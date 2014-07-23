
#include "PlayerProtocol.h"
#include "base/ccMacros.h"

PLAYER_NS_BEGIN

PlayerProtocol *PlayerProtocol::_instance = nullptr;

PlayerProtocol::PlayerProtocol()
: _fileDialogService(nullptr)
, _messageBoxService(nullptr)
, _menuService(nullptr)
, _editBoxService(nullptr)
{
    CCASSERT(_instance == nullptr, "CAN NOT CREATE MORE PLAYER INSTANCE");
    _instance = this;
}

PlayerProtocol::~PlayerProtocol()
{
    PLAYER_SAFE_DELETE(_fileDialogService);
    PLAYER_SAFE_DELETE(_messageBoxService);
    PLAYER_SAFE_DELETE(_menuService);
    PLAYER_SAFE_DELETE(_editBoxService);
    _instance = nullptr;
}

PlayerProtocol *PlayerProtocol::getInstance()
{
    return _instance;
}

void PlayerProtocol::purgeInstance()
{
    PLAYER_SAFE_DELETE(_instance);
}

void PlayerProtocol::setPlayerSettings(const PlayerSettings &settings)
{
    _settings = settings;
}

PlayerSettings PlayerProtocol::getPlayerSettings() const
{
    return _settings;
}

PLAYER_NS_END
