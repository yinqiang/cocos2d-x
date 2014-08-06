
#ifndef __PLAYER_MESSAGEBOX_SERVICE_WIN_H_
#define __PLAYER_MESSAGEBOX_SERVICE_WIN_H_

#include <string>
#include <unordered_map>

using namespace std;

#include "cocos2d.h"

using namespace cocos2d;

#include "stdafx.h"
#include "PlayerMessageBoxServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerMessageBoxServiceWin : public PlayerMessageBoxServiceProtocol
{
public:
    PlayerMessageBoxServiceWin(HWND hwnd);

    virtual int showMessageBox(const string &title, const string &message, int buttonsType = BUTTONS_OK);

protected:
    HWND _hwnd;
};

PLAYER_NS_END

#endif // __PLAYER_MESSAGEBOX_SERVICE_WIN_H_
