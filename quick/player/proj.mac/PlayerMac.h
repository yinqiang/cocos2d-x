
#ifndef __PLAYER_MAC_H_
#define __PLAYER_MAC_H_

#include "PlayerProtocol.h"

#include "PlayerEditBoxServiceMac.h"
#include "PlayerFileDialogServiceMac.h"
#include "PlayerMenuServiceMac.h"
#include "PlayerMessageBoxServiceMac.h"

#include "player_tolua.h"
#include "PlayerUtils.h"

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
    
protected:
    Player();
    
    PlayerMenuServiceMac        *_menuService;
    PlayerMessageBoxServiceMac  *_messageBoxService;
    PlayerFileDialogServiceMac  *_fileDialogService;
    PlayerEditBoxServiceMac     *_editBoxService;
};

PLAYER_NS_END

#endif // __PLAYER_MAC_H_
