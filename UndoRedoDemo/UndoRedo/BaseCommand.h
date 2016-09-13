#pragma once

#include "Factory.h"

class BaseCommand
{
public:
    virtual ~BaseCommand() {}
    virtual bool Execute() = 0;
    virtual bool Unexecute() = 0;

    static BaseCommand * CreateCommand(const std::string& strCommand)
    {
        return Factory<BaseCommand, const std::string>::instance()->CreateObject(strCommand);
    }
};

template <class DerivedCommand> 
class RegisterCommandClass
{
public:
    static BaseCommand * Create()
    {
        return new DerivedCommand;
    }
    RegisterCommandClass(const std::string& strId)
    {
        Factory<BaseCommand, const std::string>::instance()->Register(strId, RegisterCommandClass::Create);
    }
};

#define CREATECOMMAND(Command) BaseCommand::CreateCommand(ClassNameToString(Command))
