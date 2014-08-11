
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <Commdlg.h>
#include <Shlobj.h>
#include <winnls.h>
#include <shobjidl.h>
#include <objbase.h>
#include <objidl.h>
#include <shlguid.h>
#include <shellapi.h>

#include "PlayerWin.h"

#include "glfw3.h"
#include "glfw3native.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    auto player = player::PlayerWin::create();
    return player->run();
}

PLAYER_NS_BEGIN

PlayerWin::PlayerWin()
: _app(nullptr)
, _hwnd(NULL)
, _writeDebugLogFile(nullptr)
, _menuService(nullptr)
, _messageBoxService(nullptr)
{
}

PlayerWin::~PlayerWin()
{
    CC_SAFE_DELETE(_menuService);
    CC_SAFE_DELETE(_messageBoxService);
    CC_SAFE_DELETE(_fileDialogService);
    CC_SAFE_DELETE(_app);
    if (_writeDebugLogFile)
    {
        fclose(_writeDebugLogFile);
    }
}

PlayerWin *PlayerWin::create()
{
    return new PlayerWin();
}

PlayerFileDialogServiceProtocol *PlayerWin::getFileDialogService()
{
    return nullptr;
}

PlayerMessageBoxServiceProtocol *PlayerWin::getMessageBoxService()
{
    return nullptr;
}

PlayerMenuServiceProtocol *PlayerWin::getMenuService()
{
    return _menuService;
}

PlayerEditBoxServiceProtocol *PlayerWin::getEditBoxService()
{
    return nullptr;
}

int PlayerWin::run()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    // set QUICK_V3_ROOT
    const char *QUICK_V3_ROOT = getenv("QUICK_V3_ROOT");
    if (!QUICK_V3_ROOT || strlen(QUICK_V3_ROOT) == 0)
    {
        MessageBox("Please run \"setup_win.bat\", set quick-cocos2d-x root path.", "quick-cocos2d-x player error");
        return 1;
    }
    SimulatorConfig::getInstance()->setQuickCocos2dxRootPath(QUICK_V3_ROOT);

    // load project config from command line args
    vector<string> args;
    for (int i = 0; i < __argc; ++i)
    {
        wstring ws(__wargv[i]);
        string s;
        s.assign(ws.begin(), ws.end());
        args.push_back(s);
    }
    _project.parseCommandLine(args);

    // create the application instance
    _app = new AppDelegate();
    _app->setProjectConfig(_project);

    // set environments
    SetCurrentDirectoryA(_project.getProjectDir().c_str());
    FileUtils::getInstance()->setSearchRootPath(_project.getProjectDir().c_str());
    FileUtils::getInstance()->setWritablePath(_project.getWritableRealPath().c_str());

    // check screen DPI
    HDC screen = GetDC(0);
    int dpi = GetDeviceCaps(screen, LOGPIXELSX);
    ReleaseDC(0, screen);

    // set scale with DPI
    //  96 DPI = 100 % scaling
    // 120 DPI = 125 % scaling
    // 144 DPI = 150 % scaling
    // 192 DPI = 200 % scaling
    // http://msdn.microsoft.com/en-us/library/windows/desktop/dn469266%28v=vs.85%29.aspx#dpi_and_the_desktop_scaling_factor
    //
    // enable DPI-Aware with DeclareDPIAware.manifest
    // http://msdn.microsoft.com/en-us/library/windows/desktop/dn469266%28v=vs.85%29.aspx#declaring_dpi_awareness
    float screenScale = 1.0f;
    if (dpi >= 120 && dpi < 144)
    {
        screenScale = 1.25f;
    }
    else if (dpi >= 144 && dpi < 192)
    {
        screenScale = 1.5f;
    }
    else if (dpi >= 192)
    {
        screenScale = 2.0f;
    }
    CCLOG("SCREEN DPI = %d, SCREEN SCALE = %0.2f", dpi, screenScale);

    // create opengl view
    Size frameSize = _project.getFrameSize();
    float frameScale = 1.0f;
    if (_project.isRetinaDisplay())
    {
        frameSize.width *= screenScale;
        frameSize.height *= screenScale;
    }
    else
    {
        frameScale = screenScale;
    }

    const Rect frameRect = Rect(0, 0, frameSize.width, frameSize.height);
    bool isResize = (!_project.isDialog()) && _project.isResizeWindow();
    bool isDecorated = !_project.isDialog();
    auto glview = GLView::createWithRect("quick-cocos2d-x", frameRect, frameScale, isResize, false, isDecorated);
    auto director = Director::getInstance();
    director->setOpenGLView(glview);
    director->setScreenScale(frameScale);
    ResolutionPolicy policy = _project.isResizeWindow() ? ResolutionPolicy::FILL_ALL : ResolutionPolicy::NO_BORDER;
    director->setContentScaleFactor(screenScale);
    glview->setDesignResolutionSize(frameSize.width, frameSize.height, policy);

    GLFWwindow *window = glview->getWindow();
    _hwnd = glfwGetWin32Window(window);
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // init player services
    initServices();

    if (isDecorated && GetMenu(_hwnd))
    {
        // after create MenuBar, resize window and show window
        glfwSetWindowSize(window, width, height + GetSystemMetrics(SM_CYMENU));

        // Force update window, -_-#
        RECT rect;
        GetWindowRect(_hwnd, &rect);
        MoveWindow(_hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top + 1, TRUE);
        HWND hwndCallback = _hwnd;
        director->getScheduler()->schedule([hwndCallback, rect](float dt) {
            CCLOG("SHOW_WINDOW_CALLBACK %0.2f", dt);
            MoveWindow(hwndCallback, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
            glfwShowWindow(Director::getInstance()->getOpenGLView()->getWindow());
        }, this, 1.0f / 60.0f, 0, 0.0f, false, "SHOW_WINDOW_CALLBACK");
    }

    // register event handlers
    auto eventDispatcher = director->getEventDispatcher();
    eventDispatcher->addCustomEventListener("APP.WINDOW_CLOSE_EVENT", CC_CALLBACK_1(PlayerWin::onWindowClose, this));
    eventDispatcher->addCustomEventListener("APP.WINDOW_RESIZE_EVENT", CC_CALLBACK_1(PlayerWin::onWindowResize, this));

    // startup message loop
    _project.dump();
    auto app = Application::getInstance();
    return app->run();
}

// services
void PlayerWin::initServices()
{
    CCASSERT(_menuService == nullptr, "CAN'T INITIALIZATION SERVICES MORE THAN ONCE");
    _menuService = new PlayerMenuServiceWin(_hwnd);
    _messageBoxService = new PlayerMessageBoxServiceWin(_hwnd);
    _fileDialogService = new PlayerFileDialogServiceWin(_hwnd);
    _editboxService = new PlayerEditBoxServiceWin(_hwnd);

    if (_project.isDialog())
    {
        // remove menu
        SetMenu(_hwnd, NULL);
    }

    //CCLOG("saveFile = %s", _fileDialogService->saveFile("TITLE", "C:\\Work\\hello.lua").c_str());

    //vector<string> files = _fileDialogService->openMultiple("中文描述内容", "C:\\Work", "Lua Script File|*.lua;JSON File|*.json");
    //for (auto it = files.begin(); it != files.end(); ++it)
    //{
    //    CCLOG("openMultiple = %s", (*it).c_str());
    //}

    PlayerMenuServiceProtocol *service = getMenuService();
    service->addItem("FILE", "&File");
    service->addItem("FILE_OPEN", "&Open", "FILE");
    service->addItem("FILE_OPEN_RECENTS", "Open &Recents", "FILE")->setEnabled(true);
    service->addItem("FILE_OPEN_RECENTS_1", "<recent 1>", "FILE_OPEN_RECENTS")->setTitle("<recent 1x>");
    service->addItem("FILE_OPEN_RECENTS_2", "<recent 2>", "FILE_OPEN_RECENTS")->setEnabled(false);
    service->addItem("FILE_OPEN_RECENTS_3", "<recent 3>", "FILE_OPEN_RECENTS");
    service->addItem("FILE_OPEN_RECENTS_4", "<recent 4>", "FILE_OPEN_RECENTS")->setChecked(true);
    service->addItem("FILE_SAVE", "&Save", "FILE");
    service->addItem("FILE_SAVE_AS", "Save &As...", "FILE");
    service->addItem("FILE_SEP1", "-", "FILE");
    service->addItem("FILE_EXIT", "E&xit", "FILE");

    service->addItem("VIEW", "&View");
    service->addItem("VIEW_PORTRAIT", "&Portrait", "VIEW");
    service->addItem("VIEW_LANDSCAPE", "&Landscape", "VIEW");

    CCLOG("------------------------");
    CCLOG("FILE order = %d", service->getItem("FILE")->getOrder());
    CCLOG("FILE_OPEN order = %d", service->getItem("FILE_OPEN")->getOrder());
    CCLOG("FILE_OPEN_RECENTS order = %d", service->getItem("FILE_OPEN_RECENTS")->getOrder());
    CCLOG("FILE_SAVE order = %d", service->getItem("FILE_SAVE")->getOrder());
    CCLOG("FILE_SAVE_AS order = %d", service->getItem("FILE_SAVE_AS")->getOrder());
    CCLOG("FILE_SEP1 order = %d", service->getItem("FILE_SEP1")->getOrder());
    CCLOG("FILE_EXIT order = %d", service->getItem("FILE_EXIT")->getOrder());
    CCLOG("------------------------");

    service->removeItem("VIEW");
    service->removeItem("FILE_OPEN_RECENTS_3");
}

// event handlers
void PlayerWin::onWindowClose(EventCustom* event)
{
    CCLOG("APP.WINDOW_CLOSE_EVENT");

    // If script set event's result to "cancel", ignore window close event
    EventCustom forwardEvent("APP.EVENT");
    stringstream buf;
    buf << "{\"name\":\"close\"}";
    forwardEvent.setDataString(buf.str());
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&forwardEvent);

    cocos2d::Rect rect(100, 50, 500, 380);
    _editboxService->setFont("Microsoft YaHei", 11);
    _editboxService->showMultiLineEditBox(rect);

    //if (forwardEvent.getResult().compare("cancel") != 0)
    //{
    glfwSetWindowShouldClose(Director::getInstance()->getOpenGLView()->getWindow(), 0);
    //}
}

void PlayerWin::onWindowResize(EventCustom* event)
{
    RECT rect;
    GetClientRect(_hwnd, &rect);
    CCLOG("width = %d, height = %d", rect.right - rect.left, rect.bottom - rect.top);
}

// debug log
void PlayerWin::writeDebugLog(const char *log)
{

}

PLAYER_NS_END
