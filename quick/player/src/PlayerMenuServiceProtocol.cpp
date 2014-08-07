
#include "PlayerMenuServiceProtocol.h"
#include "CCLuaEngine.h"

PLAYER_NS_BEGIN

PlayerMenuItem::PlayerMenuItem()
: _order(0)
, _isGroup(false)
, _isEnabled(true)
, _isChecked(false)
{
}

PlayerMenuItem::~PlayerMenuItem()
{
}

string PlayerMenuItem::getMenuId() const
{
    return _menuId;
}

string PlayerMenuItem::getTitle() const
{
    return _title;
}

int PlayerMenuItem::getOrder() const
{
    return _order;
}

bool PlayerMenuItem::isGroup() const
{
    return _isGroup;
}

bool PlayerMenuItem::isEnabled() const
{
    return _isEnabled;
}

bool PlayerMenuItem::isChecked() const
{
    return _isChecked;
}

string PlayerMenuItem::getShortcut() const
{
    return _shortcut;
}

PLAYER_NS_END
