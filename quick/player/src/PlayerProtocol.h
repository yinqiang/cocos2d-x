
#ifndef __PLAYER_PROTOCOL_H_
#define __PLAYER_PROTOCOL_H_

#include "PlayerMacros.h"

#include "PlayerFileDialogServiceProtocol.h"
#include "PlayerMessageBoxServiceProtocol.h"
#include "PlayerMenuServiceProtocol.h"
#include "PlayerEditBoxServiceProtocol.h"

#include "PlayerUtils.h"
#include "PlayerSettings.h"

PLAYER_NS_BEGIN

class PlayerProtocol
{
public:
    virtual ~PlayerProtocol();

    static PlayerProtocol *getInstance();
    static void purgeInstance();

    void setPlayerSettings(const PlayerSettings &settings);
    PlayerSettings getPlayerSettings() const;

    virtual PlayerFileDialogServiceProtocol *getFileDialogService() = 0; // implemented in platform related source files
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService() = 0;
    virtual PlayerMenuServiceProtocol       *getMenuService() = 0;
    virtual PlayerEditBoxServiceProtocol    *getEditBoxService() = 0;

protected:
    PlayerProtocol(); // avoid create instance from outside

    PlayerSettings _settings;

    PlayerFileDialogServiceProtocol *_fileDialogService;
    PlayerMessageBoxServiceProtocol *_messageBoxService;
    PlayerMenuServiceProtocol       *_menuService;
    PlayerEditBoxServiceProtocol    *_editBoxService;

private:
    static PlayerProtocol *_instance;
};

PLAYER_NS_END

#endif // __PLAYER_PROTOCOL_H_
