
#ifndef __PLAYER_MAC_H_
#define __PLAYER_MAC_H_

#include "PlayerProtocol.h"

#include "PlayerEditBoxServiceMac.h"
#include "PlayerFileDialogServiceMac.h"
#include "PlayerMenuServiceMac.h"
#include "PlayerMessageBoxServiceMac.h"

#include "player_tolua.h"
#include "PlayerUtils.h"

#include "ProjectConfig/ProjectConfig.h"
PLAYER_NS_BEGIN

class Player : public PlayerProtocol
{
public:
    static Player *create();
    virtual ~Player();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService();

    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService();
    
    virtual PlayerMenuServiceProtocol       *getMenuService();
    
    virtual PlayerEditBoxServiceProtocol    *getEditBoxService();
    
    virtual PlayerTaskServiceProtocol       *getTaskService();
    
    //
    void quit();
    void relaunch();
    void openNewPlayer();
    void openNewPlayerWithProjectConfig(ProjectConfig config);
    void openProjectWithProjectConfig(ProjectConfig config);
    
    void setController(id controller);
protected:
    Player();
    
    PlayerMenuServiceMac        *_menuService;
    PlayerMessageBoxServiceMac  *_messageBoxService;
    PlayerFileDialogServiceMac  *_fileDialogService;
    PlayerEditBoxServiceMac     *_editBoxService;
    
    id                          _appController;
};

PLAYER_NS_END

#endif // __PLAYER_MAC_H_
