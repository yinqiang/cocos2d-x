
#ifndef __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_
#define __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_

#include <string>
#include <vector>

using namespace std;

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerFileDialogServiceProtocol : public PlayerServiceProtocol
{
public:
    /**
     * extensions = "Lua Script File|*.lua;JSON File|*.json";
     */
    virtual string openFile(const string &title, const string &directory, const string &extensions) const = 0;
    virtual vector<string> openMultiple(const string &title, const string &directory, const string &extensions) const = 0;
    virtual string saveFile(const string &title, const string &path) const = 0;
    virtual string openDirectory(const string &title, const string &directory) const = 0;
};

PLAYER_NS_END

#endif // __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_
