
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

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    return player::Player::startup();
}

PLAYER_NS_BEGIN

Player *Player::_instance = NULL;

Player::Player()
: _app(NULL)
, _hwnd(NULL)
, _writeDebugLogFile(NULL)
{
}

Player::~Player()
{
    if (_writeDebugLogFile)
    {
        fclose(_writeDebugLogFile);
    }
    if (_app)
    {
        delete _app;
    }
}

int Player::startup()
{
    Player *player = Player::getInstance();
    int ret = player->run();
    delete player;
    return ret;
}

Player *Player::getInstance()
{
    if (!_instance)
    {
        _instance = new Player();
    }
    return _instance;
}

AppDelegate *Player::getApp()
{
    return _app;
}

HWND Player::getWindowHandle()
{
    return _hwnd;
}

int Player::run()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    // set QUICK_V3_ROOT
    const char *QUICK_V3_ROOT = getenv("QUICK_V3_ROOT");
    SimulatorConfig::getInstance()->setQuickCocos2dxRootPath(QUICK_V3_ROOT);

    // create the application instance
    _app = new AppDelegate();
    _app->setProjectConfig(_project);

    // set environments
    SetCurrentDirectoryA(_project.getProjectDir().c_str());
    FileUtils::getInstance()->setSearchRootPath(_project.getProjectDir().c_str());
    FileUtils::getInstance()->setWritablePath(_project.getWritableRealPath().c_str());

    // create opengl view
    const Size frameSize = _project.getFrameSize();
    auto glview = GLView::createWithRect("player", cocos2d::Rect(0, 0, frameSize.width, frameSize.height), _project.getFrameScale(), false);
    Director::getInstance()->setOpenGLView(glview);

    // startup message loop
    return Application::getInstance()->run();
}

void Player::relaunch(const string &commandLine)
{

}

void Player::writeDebugLog(const char *log)
{

}

// windows callback
LRESULT Player::WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL *pProcessed)
{
    return 0;
}

PLAYER_NS_END
