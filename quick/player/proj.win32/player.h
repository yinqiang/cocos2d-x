#pragma once

#include <string>

using namespace std;

#include "resource.h"

#include "cocos2d.h"
#include "ProjectConfig/ProjectConfig.h"
#include "ProjectConfig/SimulatorConfig.h"

using namespace cocos2d;

#include "PlayerMacros.h"
#include "AppDelegate.h"

PLAYER_NS_BEGIN

class CC_DLL Player : public Ref
{
public:
    static int startup();
    ~Player();

private:
    static Player *getInstance();
    static Player *_instance;

    AppDelegate *getApp();
    HWND getWindowHandle();

    Player();

    AppDelegate *_app;
    ProjectConfig _project;
    HWND _hwnd;
    FILE *_writeDebugLogFile;

    int run();
    void relaunch(const string &commandLine);

    // debug log
    void writeDebugLog(const char *log);

    // windows callback
    static LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL *pProcessed);
};

PLAYER_NS_END
