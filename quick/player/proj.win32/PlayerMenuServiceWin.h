
#ifndef __PLAYER_MENU_SERVICE_WIN_H_
#define __PLAYER_MENU_SERVICE_WIN_H_

#include <string>
#include <unordered_map>

using namespace std;

#include "cocos2d.h"

using namespace cocos2d;

#include "stdafx.h"
#include "PlayerMenuServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerMenuItemWin : public PlayerMenuItem
{
public:
    static PlayerMenuItemWin *create(const string &menuId,
        const string &title);

    virtual ~PlayerMenuItemWin();

    virtual void setTitle(const string &title);
    virtual void setEnabled(bool enabled);
    virtual void setChecked(bool checked);
    virtual void setShortcut(const string &shortcut);

protected:
    PlayerMenuItemWin();

    PlayerMenuItemWin *_parent;
    UINT _commandId;
    HMENU _hmenu;
    Vector<PlayerMenuItemWin*> _children;

    friend class PlayerMenuServiceWin;
};

class PlayerMenuServiceWin : public PlayerMenuServiceProtocol
{
public:
    PlayerMenuServiceWin(HWND hwnd);
    virtual ~PlayerMenuServiceWin();

    virtual PlayerMenuItem *addItem(const string &menuId, const string &title, const string &parentId, int order = MAX_ORDER);
    virtual PlayerMenuItem *addItem(const string &menuId, const string &title);
    virtual PlayerMenuItem *getItem(const string &menuId);
    virtual bool removeItem(const string &menuId);

private:
    static UINT _newCommandId;

    HWND _hwnd;
    PlayerMenuItemWin _root;
    unordered_map<string, PlayerMenuItemWin*> _items;
    unordered_map<UINT, string> _commandId2menuId;
};

PLAYER_NS_END

#endif // __PLAYER_MENU_SERVICE_WIN_H_
