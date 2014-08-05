
#include "MenuServiceWin.h"
#include "cocos2d.h"

PLAYER_NS_BEGIN

PlayerMenuItemWin *PlayerMenuItemWin::create(const string &menuId, const string &title)
{
    PlayerMenuItemWin *item = new PlayerMenuItemWin();
    item->_menuId = menuId;
    item->_title = title;
    item->autorelease();
    return item;
}

PlayerMenuItemWin::PlayerMenuItemWin()
    : _parent(nullptr)
    , _commandId(0)
    , _hmenu(NULL)
{
}

PlayerMenuItemWin::~PlayerMenuItemWin()
{
    CC_SAFE_RELEASE(_parent);
    if (_hmenu)
    {
        DestroyMenu(_hmenu);
    }
}

void PlayerMenuItemWin::setTitle(const string &title)
{

}

void PlayerMenuItemWin::setEnabled(bool enabled)
{

}

void PlayerMenuItemWin::setChecked(bool checked)
{

}

void PlayerMenuItemWin::setShortcut(const string &shortcut)
{

}

// MenuServiceWin

UINT MenuServiceWin::_newCommandId = 0x1000;

MenuServiceWin::MenuServiceWin(HWND hwnd)
{
    // create menu
    _root._commandId = 0;
    _root._hmenu = CreateMenu();
    SetMenu(hwnd, _root._hmenu);
}

MenuServiceWin::~MenuServiceWin()
{
}

PlayerMenuItem *MenuServiceWin::addItem(const string &menuId, const string &title, const string &parentId, int order /* = MAX_ORDER */)
{
    if (menuId.length() == 0 || title.length() == 0)
    {
        CCLOG("MenuServiceWin::addItem() - menuId and title must is non-empty");
        return nullptr;
    }

    // check menu id is exists
    if (_items.find(menuId) != _items.end())
    {
        CCLOG("MenuServiceWin::addItem() - menu id (%s) is exists", menuId.c_str());
        return false;
    }

    // set parent
    PlayerMenuItemWin *parent = &_root;
    if (parentId.length())
    {
        // query parent menu
        auto it = _items.find(parentId);
        if (it != _items.end())
        {
            parent = it->second;
        }
    }

    if (!parent->_hmenu)
    {
        // create menu handle for parent (convert parent to submenu)
        parent->_hmenu = CreateMenu();
        parent->_isGroup = true;
        MENUITEMINFO menuitem;
        menuitem.cbSize = sizeof(menuitem);
        menuitem.fMask = MIIM_SUBMENU;
        menuitem.hSubMenu = parent->_hmenu;
        if (!SetMenuItemInfo(parent->_parent->_hmenu, parent->_commandId, MF_BYCOMMAND, &menuitem))
        {
            DWORD err = GetLastError();
            CCLOG("MenuServiceWin::addItem() - set menu handle failed, menu id (%s). error code = %u", parent->_menuId.c_str(), err);
            return nullptr;
        }
    }

    // create new menu item
    _newCommandId++;
    PlayerMenuItemWin *item = PlayerMenuItemWin::create(menuId, title);
    item->_commandId = _newCommandId;
    item->_parent = parent;
    item->_parent->retain();

    // add menu item to menu bar
    MENUITEMINFO menuitem;
    menuitem.cbSize = sizeof(menuitem);
    menuitem.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING;
    menuitem.fType = (item->_title.compare("-") == 0) ? MFT_SEPARATOR : MFT_STRING;
    menuitem.fState = (item->_isEnabled) ? MFS_ENABLED : MFS_DISABLED;
    menuitem.fState = (item->_isChecked) ? MFS_CHECKED : MFS_UNCHECKED;
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(item->_title, u16title);
    menuitem.dwTypeData = (LPTSTR)u16title.c_str();
    menuitem.wID = _newCommandId;

    // check new menu item position
    if (order > parent->_children.size())
    {
        order = parent->_children.size();
    }
    else if (order < 0)
    {
        order = 0;
    }

    // create new menu item
    if (!InsertMenuItem(parent->_hmenu, order, TRUE, &menuitem))
    {
        DWORD err = GetLastError();
        CCLOG("MenuServiceWin::addItem() - insert new menu item failed, menu id (%s). error code = %u", item->_menuId.c_str(), err);
        item->release();
        return nullptr;
    }

    // update menu state
    parent->_children.insert(order, item);
    _items[item->_menuId] = item;
    _uid2id[item->_commandId] = item->_menuId;

    return item;
}

PlayerMenuItem *MenuServiceWin::addItem(const string &menuId, const string &title)
{
    return addItem(menuId, title, "");
}

PlayerMenuItem *MenuServiceWin::getItem(const string &menuId)
{

    return nullptr;
}

bool MenuServiceWin::removeItem(const string &menuId)
{

    return false;
}

//bool MenuServiceWin::deleteItem(const string &menuId)
//{
//    if (!menuId)
//    {
//        CCLOG("MenuServiceWin::deleteItem() - Invalid menu id");
//        return false;
//    }
//
//    auto it = _items.find(menuId);
//    if (it == _items.end())
//    {
//        CCLOG("MenuServiceWin::deleteItem() - Invalid menu id (%s)", menuId);
//        return false;
//    }
//
//    PlayerMenuItemWin *itemwin = it->second;
//    if (itemwin->children.size() == 0)
//    {
//        if (!DeleteMenu(itemwin->parent->hmenu, itemwin->uid, MF_BYCOMMAND))
//        {
//            DWORD err = GetLastError();
//            CCLOG("MenuServiceWin::deleteItem() - remove menu item failed, menu id (%s). error code = %u", itemwin->item.menuId.c_str(), err);
//            return false;
//        }
//
//        // remove item from parent
//        auto *children = &itemwin->parent->children;
//        for (auto it = children->begin(); it != children->end(); ++it)
//        {
//            if ((*it).uid == itemwin->uid)
//            {
//                CCLOG("MenuServiceWin::deleteItem() - remove menu item (%s)", itemwin->item.menuId.c_str());
//                children->erase(it);
//                break;
//            }
//        }
//        // remove menu id mapping
//        _items.erase(menuId);
//        return true;
//    }
//    else
//    {
//        while (itemwin->children.size() != 0)
//        {
//            PlayerMenuItemWin *child = &(*itemwin->children.begin());
//            if (!deleteItem(child->item.menuId.c_str()))
//            {
//                break;
//                return false;
//            }
//        }
//        return deleteItem(menuId);
//    }
//}

PLAYER_NS_END
