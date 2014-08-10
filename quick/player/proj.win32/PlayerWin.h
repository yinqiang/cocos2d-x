#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "cocos2d.h"
#include "AppDelegate.h"
#include "ProjectConfig/ProjectConfig.h"
#include "ProjectConfig/SimulatorConfig.h"

#include "PlayerMacros.h"
#include "PlayerProtocol.h"
#include "PlayerMenuServiceWin.h"
#include "PlayerMessageBoxServiceWin.h"
#include "PlayerFileDialogServiceWin.h"
#include "PlayerEditBoxServiceWin.h"

PLAYER_NS_BEGIN

class CC_DLL Player : public PlayerProtocol
{
public:
    static Player *create();
    virtual ~Player();
    int run();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService();
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService();
    virtual PlayerMenuServiceProtocol *getMenuService();
    virtual PlayerEditBoxServiceProtocol *getEditBoxService();

protected:
    Player();

    ProjectConfig _project;
    HWND _hwnd;
    AppDelegate *_app;
    FILE *_writeDebugLogFile;

    PlayerMenuServiceWin *_menuService;
    PlayerMessageBoxServiceWin *_messageBoxService;
    PlayerFileDialogServiceWin *_fileDialogService;
    PlayerEditBoxServiceWin *_editboxService;

    // services
    void initServices();

    // event handlers
    void onWindowClose(EventCustom* event);

    // debug log
    void writeDebugLog(const char *log);
};

PLAYER_NS_END
