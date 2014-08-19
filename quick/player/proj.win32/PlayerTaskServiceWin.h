
#ifndef __PLAYER_TASK_SERVICE_WIN_H_
#define __PLAYER_TASK_SERVICE_WIN_H_

#include "PlayerTaskServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerTaskWin : public PlayerTask
{
public:
    static PlayerTaskWin *create(const std::string &name,
                                 const std::string &executePath,
                                 const std::string &commandLineArguments);

    virtual bool run();
    virtual void stop();

protected:
    PlayerTaskWin(const std::string &name,
                  const std::string &executePath,
                  const std::string &commandLineArguments);

    void cleanup();
    std::u16string makeCommandLine() const;

    HANDLE _childStdInRead;
    HANDLE _childStdInWrite;
    HANDLE _childStdOutRead;
    HANDLE _childStdOutWrite;
    PROCESS_INFORMATION _pi;
};

class PlayerTaskServiceWin : public PlayerTaskServiceProtocol
{
public:
    PlayerTaskServiceWin(HWND hwnd);
    virtual ~PlayerTaskServiceWin();

    virtual PlayerTask *createTask(const std::string &name,
                                   const std::string &executePath,
                                   const std::string &commandLineArguments);
    virtual PlayerTask *getTask(const std::string &name);

protected:
    HWND _hwnd;
    cocos2d::Map<std::string, PlayerTaskWin*> _tasks;
};

PLAYER_NS_END

#endif // __PLAYER_TASK_SERVICE_WIN_H_
