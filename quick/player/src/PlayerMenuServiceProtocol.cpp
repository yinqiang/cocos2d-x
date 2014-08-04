
#include "PlayerMenuServiceProtocol.h"
#include "CCLuaEngine.h"

PLAYER_NS_BEGIN

PlayerMenuItem::PlayerMenuItem()
: _isGroup(false)
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
