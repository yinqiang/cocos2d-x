
#ifndef __PLAYER_MENU_SERVICE_PROTOCOL_H
#define __PLAYER_MENU_SERVICE_PROTOCOL_H

#include <string>

using namespace std;

#include "cocos2d.h"

using namespace cocos2d;

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

#define kPlayerSuperModifyKey "super"
#define kPlayerShiftModifyKey "shift"
#define kPlayerCtrlModifyKey  "ctrl"
#define kPlayerAltModifyKey   "alt"

class PlayerMenuItem : public Ref
{
public:
    virtual ~PlayerMenuItem();

    string getMenuId() const;
    string getTitle() const;
    bool isGroup() const;
    bool isEnabled() const;
    bool isChecked() const;
    string getShortcut() const;

    virtual void setTitle(const string &title) = 0;
    virtual void setEnabled(bool enabled) = 0;
    virtual void setChecked(bool checked) = 0;
    virtual void setShortcut(const string &shortcut) = 0;

protected:
    PlayerMenuItem();

    string _menuId;
    string _title;
    bool _isGroup;
    bool _isEnabled;
    bool _isChecked; // ignored when isGroup = true
    string _shortcut; // ignored when isGroup = true
};

class PlayerMenuServiceProtocol : public PlayerServiceProtocol
{
public:
    static const int MAX_ORDER = 9999;

    virtual PlayerMenuItem *addItem(const string &menuId, const string &title, const string &parentId, int order = MAX_ORDER) = 0;
    virtual PlayerMenuItem *addItem(const string &menuId, const string &title) = 0;
    virtual PlayerMenuItem *getItem(const string &menuId) = 0;
    virtual bool removeItem(const string &menuId) = 0;
}; 

PLAYER_NS_END

#endif // __PLAYER_MENU_SERVICE_PROTOCOL_H
