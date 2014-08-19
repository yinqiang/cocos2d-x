
#ifndef __PLAYER_TASK_SERVICE_PROTOCOL_H
#define __PLAYER_TASK_SERVICE_PROTOCOL_H

#include <string>

#include "cocos2d.h"
#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerTask : public cocos2d::Ref
{
public:
    static const int STATE_IDLE = 0;
    static const int STATE_RUNNING = 1;
    static const int STATE_COMPLETED = 2;

    virtual ~PlayerTask() {};

    std::string getName() const
    {
        return _name;
    }

    std::string getExecutePath() const
    {
        return _executePath;
    }

    std::string getCommandLineArguments() const
    {
        return _commandLineArguments;
    }

    std::string getOutput() const
    {
        return _output;
    }

    int getState() const
    {
        return _state;
    }

    bool isIdle() const
    {
        return _state == STATE_IDLE;
    }

    bool isRunning() const
    {
        return _state == STATE_RUNNING;
    }

    bool isCompleted() const
    {
        return _state == STATE_COMPLETED;
    }

    float getLifetime() const
    {
        return _lifetime;
    }

    int getResultCode() const
    {
        return _resultCode;
    }

    virtual bool run() = 0;
    virtual void stop() = 0;

protected:
    PlayerTask(const std::string &name,
               const std::string &executePath,
               const std::string &commandLineArguments)
               : _name(name)
               , _executePath(executePath)
               , _commandLineArguments(commandLineArguments)
               , _state(STATE_IDLE)
               , _lifetime(0)
               , _resultCode(0)
    {
    }

    std::string _name;
    std::string _executePath;
    std::string _commandLineArguments;
    std::string _output;
    float _lifetime;
    int _state;
    int _resultCode;
};

class PlayerTaskServiceProtocol : public PlayerServiceProtocol
{
public:
    virtual PlayerTask *createTask(const std::string &name,
                                   const std::string &executePath,
                                   const std::string &commandLineArguments) = 0;
    virtual PlayerTask *getTask(const std::string &name) = 0;
    virtual void removeTask(const std::string &name) = 0;
};

PLAYER_NS_END

#endif // __PLAYER_TASK_SERVICE_PROTOCOL_H
