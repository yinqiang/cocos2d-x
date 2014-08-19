
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

    int getResultCode() const
    {
        return _resultCode;
    }

    virtual bool run() const = 0;
    virtual void stop() = 0;

protected:
    PlayerTask(const std::string &name,
               const std::string &executePath,
               const std::string &commandLineArguments)
               : _name(name)
               , _executePath(executePath)
               , _commandLineArguments(commandLineArguments)
               , _resultCode(0)
    {
    }

    std::string _name;
    std::string _executePath;
    std::string _commandLineArguments;
    std::string _output;
    int _resultCode;
};

class PlayerTaskServiceProtocol : public PlayerServiceProtocol
{
public:
    virtual PlayerTask *createTask(const std::string &name, const std::string &commandLine) = 0;
    virtual PlayerTask *getTask(const std::string &name) = 0;
};

PLAYER_NS_END

#endif // __PLAYER_TASK_SERVICE_PROTOCOL_H
