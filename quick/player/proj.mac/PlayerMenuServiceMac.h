
#ifndef __PLAYER_MENU_SERVICE_MAC_H_
#define __PLAYER_MENU_SERVICE_MAC_H_

#include <unordered_map>

#include "cocos2d.h"
#include "PlayerMacros.h"
#include "PlayerMenuServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerMenuItemMac : public PlayerMenuItem
{
public:
    static PlayerMenuItemMac *create(const string &menuId, const string &title);
    virtual ~PlayerMenuItemMac();

    virtual void setTitle(const string &title);
    virtual void setEnabled(bool enabled);
    virtual void setChecked(bool checked);
    virtual void setShortcut(const string &shortcut);

protected:
    PlayerMenuItemMac();

    PlayerMenuItemMac *_parent;
    cocos2d::Vector<PlayerMenuItemMac*> _children;

    friend class PlayerMenuServiceMac;
};

class PlayerMenuServiceMac : public PlayerMenuServiceProtocol
{
public:
    PlayerMenuServiceMac();
    virtual ~PlayerMenuServiceMac();

    virtual PlayerMenuItem *addItem(const string &menuId, const string &title, const string &parentId, int order = MAX_ORDER);
    virtual PlayerMenuItem *addItem(const string &menuId, const string &title);
    virtual PlayerMenuItem *getItem(const string &menuId);
    virtual bool removeItem(const string &menuId);

private:
    void removeIdRecursion(NSMenuItem *menuItem);
    void removeId(NSMenuItem *menuItem);
    void addId(const std::string &menuIt, NSMenuItem *menuItem);

private:
    std::unordered_map<std::string, id> m_id2Menu;
    std::unordered_map<id, std::string> m_menu2Id;
};

PLAYER_NS_END

#endif // __PLAYER_MENU_SERVICE_MAC_H_
