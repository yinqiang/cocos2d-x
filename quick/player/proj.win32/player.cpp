
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include "player.h"
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

#include "glfw3.h"
#include "glfw3native.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    auto player = player::Player::create();
    return player->run();
}

PLAYER_NS_BEGIN

Player::Player()
: _app(nullptr)
, _hwnd(NULL)
, _writeDebugLogFile(nullptr)
, _menuService(nullptr)
{
    _luastack = LuaStack::create();
    _luastack->retain();
}

Player::~Player()
{
    CC_SAFE_RELEASE(_luastack);
    if (_writeDebugLogFile)
    {
        fclose(_writeDebugLogFile);
    }
    if (_menuService)
    {
        delete _menuService;
    }
    if (_app)
    {
        delete _app;
    }
}

Player *Player::create()
{
    return new Player();
}

PlayerFileDialogServiceProtocol *Player::getFileDialogService()
{
    return nullptr;
}

PlayerMessageBoxServiceProtocol *Player::getMessageBoxService()
{
    return nullptr;
}

PlayerMenuServiceProtocol *Player::getMenuService()
{
    return _menuService;
}

PlayerEditBoxServiceProtocol *Player::getEditBoxService()
{
    return nullptr;
}

int Player::run()
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

    // create opengl view
    const Size frameSize = _project.getFrameSize();
    const Rect frameRect = Rect(0, 0, frameSize.width, frameSize.height);
    auto glview = GLView::createWithRect("quick-cocos2d-x", frameRect, screenScale, false, false);
    auto director = Director::getInstance();
    director->setOpenGLView(glview);

    GLFWwindow *window = glview->getWindow();
    _hwnd = glfwGetWin32Window(window);
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // init player services
    initServices();

    // after update UI, resize window and show window
    glfwSetWindowSize(window, width, height + GetSystemMetrics(SM_CYMENU));

    // Force update window, -_-#
    RECT rect;
    GetWindowRect(_hwnd, &rect);
    MoveWindow(_hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top + 1, FALSE);

    glfwShowWindow(window);

    // register event handlers
    auto eventDispatcher = director->getEventDispatcher();
    eventDispatcher->addCustomEventListener("APP.WINDOW_CLOSE_EVENT", CC_CALLBACK_1(Player::onWindowClose, this));

    // startup message loop
    _project.dump();
    auto app = Application::getInstance();
    return app->run();
}

// services
void Player::initServices()
{
    CCASSERT(_menuService == nullptr, "CAN'T INITIALIZATION SERVICES MORE THAN ONCE");
    _menuService = new MenuServiceWin(_hwnd);

    PlayerMenuServiceProtocol *service = getMenuService();
    service->addItem("FILE", "&File");
    service->addItem("FILE_OPEN", "&Open", "FILE");
    service->addItem("FILE_OPEN_RECENTS", "Open &Recents", "FILE");
    service->addItem("FILE_OPEN_RECENTS_1", "<recent 1>", "FILE_OPEN_RECENTS")->setTitle("<recent 1x>");
    service->addItem("FILE_OPEN_RECENTS_2", "<recent 2>", "FILE_OPEN_RECENTS")->setEnabled(false);
    service->addItem("FILE_OPEN_RECENTS_3", "<recent 3>", "FILE_OPEN_RECENTS");
    service->addItem("FILE_OPEN_RECENTS_4", "<recent 4>", "FILE_OPEN_RECENTS")->setChecked(true);
    service->addItem("FILE_SEP1", "-", "FILE");
    service->addItem("FILE_EXIT", "E&xit", "FILE");

    service->addItem("VIEW", "&View");
    service->addItem("VIEW_PORTRAIT", "&Portrait", "VIEW");
    service->addItem("VIEW_LANDSCAPE", "&Landscape", "VIEW");

    service->removeItem("VIEW");
    service->removeItem("FILE_OPEN_RECENTS_3");
}

// event handlers
void Player::onWindowClose(EventCustom* event)
{
    CCLOG("APP.WINDOW_CLOSE_EVENT");

    // If script set event's result to "cancel", ignore window close event
    EventCustom forwardEvent("APP.EVENT");
    stringstream buf;
    buf << "{\"name\":\"close\"}";
    forwardEvent.setDataString(buf.str());
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&forwardEvent);

    if (forwardEvent.getResult().compare("cancel") != 0)
    {
        glfwSetWindowShouldClose(Director::getInstance()->getOpenGLView()->getWindow(), 1);
    }
}

// debug log

void Player::writeDebugLog(const char *log)
{

}

PLAYER_NS_END
