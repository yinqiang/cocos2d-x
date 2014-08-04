
#ifndef __MENU_SERVICE_WIN_H_
#define __MENU_SERVICE_WIN_H_

#include <string>
#include <unordered_map>
#include <vector>

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

    friend class MenuServiceWin;
};

class MenuServiceWin : public PlayerMenuServiceProtocol
{
public:
    MenuServiceWin(HWND hwnd);
    virtual ~MenuServiceWin();

    virtual PlayerMenuItem *addItem(const string &menuId,
                                    const string &title,
                                    const string &parentId,
                                    int order = MAX_ORDER);
    virtual PlayerMenuItem *getItem(const string &menuId);
    virtual bool removeItem(const string &menuId);

private:
    static UINT _newCommandId;

    PlayerMenuItemWin _root;
    unordered_map<string, PlayerMenuItemWin*> _items;
};

PLAYER_NS_END

#endif // __MENU_SERVICE_WIN_H_
