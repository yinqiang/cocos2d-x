
#include <string.h>

#include "stdafx.h"
#include <Windowsx.h>
#include <Shlobj.h>
#include <Commdlg.h>

#include "cocos2d.h"

using namespace cocos2d;

#include "PlayerUtils.h"
#include "PlayerFileDialogServiceWin.h"

PLAYER_NS_BEGIN

PlayerFileDialogServiceWin::PlayerFileDialogServiceWin(HWND hwnd)
: _hwnd(hwnd)
{
}

string PlayerFileDialogServiceWin::openFile(const string &title, const string &directory, const string &extensions) const
{
    vector<string> result = openMultipleInternal(title, directory, extensions, false);
    if (result.size())
    {
        return result.at(0);
    }
    return string();
}

vector<string> PlayerFileDialogServiceWin::openMultiple(const string &title, const string &directory, const string &extensions) const
{
    return openMultipleInternal(title, directory, extensions, true);
}

string PlayerFileDialogServiceWin::saveFile(const string &title, const string &path) const
{
    u16string u16title;
    StringUtils::UTF8ToUTF16(title, u16title);

    WCHAR buff[MAX_PATH + 1] = {0};
    if (path.length() > 0)
    {
        u16string u16filename;
        StringUtils::UTF8ToUTF16(path, u16filename);
        wcscpy_s(buff, (WCHAR*)u16filename.c_str());
    }

    OPENFILENAME ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = _hwnd;
    ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
    ofn.lpstrTitle = (LPCTSTR)u16title.c_str();
    ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_LONGNAMES;
    ofn.lpstrFile = buff;
    ofn.nMaxFile = MAX_PATH;

    string result;
    if (!GetSaveFileName(&ofn))
    {
        // user cancel dialog, GetOpenFileName(will return FALSE
        DWORD err = CommDlgExtendedError();
        if (err)
        {
            CCLOG("PlayerFileDialogServiceWin::saveFile() - failed, title (%s),  error code = %u", title.c_str(), err);
        }
        return result;
    }

    StringUtils::UTF16ToUTF8((char16_t*)buff, result);
    return result;
}

// for openDirectory
int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED && lpData)
    {
        LPCTSTR path = (LPCTSTR)lpData;
        SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
    }
    return 0;
}

string PlayerFileDialogServiceWin::openDirectory(const string &title, const string &directory) const
{
    u16string u16title;
    StringUtils::UTF8ToUTF16(title, u16title);

    WCHAR basedir[MAX_PATH + 1];
    if (directory.length())
    {
        u16string u16directory;
        StringUtils::UTF8ToUTF16(directory, u16directory);
        wcscpy_s(basedir, (WCHAR*)u16directory.c_str());
    }
    else
    {
        GetCurrentDirectory(MAX_PATH, basedir);
    }

    WCHAR buff[MAX_PATH + 1] = {0};
    BROWSEINFO bi = {0};
    bi.hwndOwner = _hwnd;
    bi.pszDisplayName = buff;
    bi.lpszTitle = (LPCTSTR)u16title.c_str();
    bi.lParam = (LPARAM)basedir;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseFolderCallback;

    PIDLIST_ABSOLUTE pid = SHBrowseForFolder(&bi);
    if (pid)
    {
        SHGetPathFromIDList(pid, buff);
        string result;
        StringUtils::UTF16ToUTF8((char16_t*)buff, result);
        return result;
    }
    else
    {
        return string("");
    }
}

LPTSTR PlayerFileDialogServiceWin::parseExtensions(const string &extensions) const
{
    static WCHAR *defaultExtensions = L"All Files (*.*)\0*.*\0";
    if (extensions.length() == 0)
    {
        WCHAR *buff = new WCHAR[wcslen(defaultExtensions) + 1];
        wcscpy(buff, defaultExtensions);
        return buff;
    }

    // "Lua Script File|*.lua;JSON File|*.json"
    // to
    // "Lua Script File (*.lua)\0*.lua\0JSON File (*.json)\0*.json\0";
    u16string u16extensions;
    u16string split1((char16_t*)L";");
    u16string split2((char16_t*)L"|");
    StringUtils::UTF8ToUTF16(extensions, u16extensions);
    vector<u16string> pairs = splitString(u16extensions, split1);

    size_t buffsize = extensions.length() * 6;
    WCHAR *buff = new WCHAR[buffsize];
    memset(buff, 0, sizeof(WCHAR) * buffsize);
    size_t offset = 0;
    for (auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        vector<u16string> p = splitString(*it, split2);
        u16string descr, ext;
        if (p.size() < 2)
        {
            descr = ext = *it;
        }
        else
        {
            descr = p.at(0);
            ext = p.at(1);
        }

        wcscat(buff + offset, (WCHAR*)descr.c_str());
        wcscat(buff + offset, L" (");
        wcscat(buff + offset, (WCHAR*)ext.c_str());
        wcscat(buff + offset, L")");
        offset += descr.length() + ext.length() + 4;
        wcscat(buff + offset, (WCHAR*)ext.c_str());
        offset += ext.length() + 1;
    }
    
    return buff;
}

vector<string> PlayerFileDialogServiceWin::openMultipleInternal(const string &title, const string &directory, const string &extensions, bool isMulti) const
{
    u16string u16title;
    StringUtils::UTF8ToUTF16(title, u16title);

    WCHAR basedir[MAX_PATH + 1];
    if (directory.length())
    {
        u16string u16directory;
        StringUtils::UTF8ToUTF16(directory, u16directory);
        wcscpy_s(basedir, (WCHAR*)u16directory.c_str());
    }
    else
    {
        GetCurrentDirectory(MAX_PATH, basedir);
    }

    size_t buffsize = MAX_PATH;
    if (isMulti) buffsize = MAX_PATH * 64;
    WCHAR *buff = new WCHAR[buffsize + 1];
    memset(buff, 0, sizeof(WCHAR) * (buffsize + 1));

    OPENFILENAME ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = _hwnd;
    ofn.lpstrFilter = parseExtensions(extensions);
    ofn.lpstrTitle = (LPCTSTR)u16title.c_str();
    ofn.lpstrInitialDir = basedir;
    ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_LONGNAMES;
    if (isMulti) ofn.Flags |= OFN_ALLOWMULTISELECT | OFN_EXPLORER;
    ofn.lpstrFile = buff;
    ofn.nMaxFile = buffsize;

    vector<string> result;
    BOOL ret = GetOpenFileName(&ofn);
    delete[] ofn.lpstrFilter;
    if (!ret)
    {
        // user cancel dialog, GetOpenFileName(will return FALSE
        DWORD err = CommDlgExtendedError();
        if (err)
        {
            CCLOG("PlayerFileDialogServiceWin::openMultipleInternal() - failed, title (%s),  error code = %u", title.c_str(), err);
        }
        delete[] buff;
        return result;
    }

    if (isMulti)
    {
        WORD offset = 0;
        string path;
        while (buff[offset] != '\0')
        {
            string filename;
            u16string u16filename((char16_t*)(buff + offset));
            StringUtils::UTF16ToUTF8(u16filename, filename);

            if (offset == 0)
            {
                path = filename;
                if (path[path.length() - 1] != '\\')
                {
                    path.append("\\");
                }
            }
            else
            {
                result.push_back(path + filename);
            }
            offset += u16filename.length() + 1;
        }
    }
    else
    {
        string path;
        StringUtils::UTF16ToUTF8((char16_t*)buff, path);
        result.push_back(path);
    }
    delete[] buff;
    return result;
}

PLAYER_NS_END
