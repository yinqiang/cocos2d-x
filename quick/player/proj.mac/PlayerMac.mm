

#include "PlayerMac.h"


PLAYER_NS_BEGIN

Player* Player::create()
{
    return new Player();
}


Player::Player()
: PlayerProtocol()
, _fileDialogService(nullptr)
, _messageBoxService(nullptr)
, _menuService(nullptr)
, _editBoxService(nullptr)
, _appController(nullptr)
{
}


Player::~Player()
{
    CC_SAFE_DELETE(_fileDialogService);
    CC_SAFE_DELETE(_fileDialogService);
    CC_SAFE_DELETE(_messageBoxService);
    CC_SAFE_DELETE(_menuService);
    CC_SAFE_DELETE(_editBoxService);
}

PlayerFileDialogServiceProtocol *Player::getFileDialogService()
{
    if (!_fileDialogService)
    {
        _fileDialogService = new PlayerFileDialogServiceMac();
    }
    return _fileDialogService;
}

PlayerMessageBoxServiceProtocol *Player::getMessageBoxService()
{
    if (!_messageBoxService)
    {
        _messageBoxService = new PlayerMessageBoxServiceMac();
    }
    return _messageBoxService;
}

PlayerMenuServiceProtocol *Player::getMenuService()
{
    if (!_menuService)
    {
        _menuService = new PlayerMenuServiceMac();
    }
    return _menuService;
}

PlayerEditBoxServiceProtocol *Player::getEditBoxService()
{
    if (!_editBoxService)
    {
        _editBoxService = new PlayerEditBoxServiceMac();
    }
    return _editBoxService;
}

PlayerTaskServiceProtocol *Player::getTaskService()
{
    return nullptr;
}

void Player::quit()
{
    PlayerProtocol::quit();
    cocos2d::Director::getInstance()->end();
}

void Player::relaunch()
{
    PlayerProtocol::relaunch();
    
    if (_appController && [_appController respondsToSelector:NSSelectorFromString(@"relaunch")])
    {
        [_appController performSelector:NSSelectorFromString(@"relaunch")];
    }
}

void Player::openNewPlayer()
{
    PlayerProtocol::openNewPlayer();
}

void Player::openNewPlayerWithProjectConfig(ProjectConfig config)
{
    if (_appController && [_appController respondsToSelector:NSSelectorFromString(@"launch:")])
    {
        NSString *commandLine = [NSString stringWithCString:config.makeCommandLine().c_str()
                                                   encoding:NSUTF8StringEncoding];
        NSArray *arguments = [NSMutableArray arrayWithArray:[commandLine componentsSeparatedByString:@" "]];
        
        [_appController performSelector:NSSelectorFromString(@"launch:") withObject:arguments];
    }
}

void Player::openProjectWithProjectConfig(ProjectConfig config)
{
    this->openNewPlayerWithProjectConfig(config);
    this->quit();
}

void Player::setController(id controller)
{
    _appController = controller;
}

PLAYER_NS_END
