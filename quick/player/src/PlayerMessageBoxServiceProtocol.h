
#ifndef __PLAYER_MESSAGEBOX_SERVICE_PROTOCOL_H
#define __PLAYER_MESSAGEBOX_SERVICE_PROTOCOL_H

#include <string>
#include <vector>

using namespace std;

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

#define kPlayerButtonsOK          0
#define kPlayerButtonsOKCancel    1
#define kPlayerButtonsYesNo       2
#define kPlayerButtonsYesNoCancel 3

class PlayerMessageBoxServiceProtocol : public PlayerServiceProtocol
{
public:
    // Show a message box, return index of user clicked button
    //
    // @return int first button index is 0
    virtual int showMessageBox(const char *title,
        const char *message,
        int buttonsType = kPlayerButtonsOK) = 0;
};

PLAYER_NS_END

#endif
