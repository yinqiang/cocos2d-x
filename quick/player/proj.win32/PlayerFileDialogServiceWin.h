
#ifndef __PLAYER_FILE_DIALOG_SERVICE_WIN_H_
#define __PLAYER_FILE_DIALOG_SERVICE_WIN_H_

#include <string>

using namespace std;

#include "stdafx.h"
#include "PlayerFileDialogServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerFileDialogServiceWin : public PlayerFileDialogServiceProtocol
{
public:
    PlayerFileDialogServiceWin(HWND hwnd);

    virtual string openFile(const string &title, const string &directory, const string &extensions) const;
    virtual vector<string> openMultiple(const string &title, const string &directory, const string &extensions) const;
    virtual string saveFile(const string &title, const string &path) const;
    virtual string openDirectory(const string &title, const string &directory) const;

protected:
    HWND _hwnd;

    LPTSTR parseExtensions(const string &extensions) const;
    vector<string> openMultipleInternal(const string &title, const string &directory, const string &extensions, bool isMulti) const;
};

PLAYER_NS_END

#endif // __PLAYER_FILE_DIALOG_SERVICE_WIN_H_
