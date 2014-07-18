
#ifndef __PLAYER_MENU_SERVICE_PROTOCOL_H
#define __PLAYER_MENU_SERVICE_PROTOCOL_H

#include <string>

using namespace std;

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

#define kPlayerSuperModifyKey "super"
#define kPlayerShiftModifyKey "shift"
#define kPlayerCtrlModifyKey  "ctrl"
#define kPlayerAltModifyKey   "alt"


class PlayerMenuItem
{
public:
    PlayerMenuItem():
        itemId(""),
        listener(0),
        isChecked(false),
        isEnabled(true),
        shortcut("")
    {
    }

    string itemId;
    string title;
    bool isGroup;
    bool isEnabled;
    bool isChecked; // this option ignored when isGroup = true
    string shortcut; // this option ignored when isGroup = true
    int listener;
};

class PlayerMenuServiceProtocol : public PlayerServiceProtocol
{
public:
    // Add menu item
    //
    // if parentIndex <= 0, add top menu item
    virtual void addItem(PlayerMenuItem *item,
        const char *parentId = NULL,
        int order = 999) = 0;

    // Modify a menu item
    //
    // update title, shortcut, isEnabled, isChecked
    virtual void modifyItem(PlayerMenuItem *item) = 0;

    // Remove a menu item
    virtual void deleteItem(PlayerMenuItem *item) = 0;
};

PLAYER_NS_END

#endif // __PLAYER_MENU_SERVICE_PROTOCOL_H
