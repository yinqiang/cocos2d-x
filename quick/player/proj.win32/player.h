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
#include "PlayerProtocol.h"

PLAYER_NS_BEGIN

class CC_DLL Player : public PlayerProtocol
{
public:
    static Player *create();
    virtual ~Player();
    int run();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService();
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService();
    virtual PlayerMenuServiceProtocol       *getMenuService();
    virtual PlayerEditBoxServiceProtocol    *getEditBoxService();

protected:
    Player();

    ProjectConfig _project;
    AppDelegate *_app;
    FILE *_writeDebugLogFile;

    // event handlers
    void onWindowClose(EventCustom* event);

    // debug log
    void writeDebugLog(const char *log);
};

PLAYER_NS_END
