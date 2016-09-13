#pragma once

#include "Factory.h"

class BaseCommandReceiver
{
public:
    virtual ~BaseCommandReceiver() {}
    virtual bool Action(bool bUndo) = 0;

    static BaseCommandReceiver * CreateCommandReceiver(const std::string& strCommandReceiver)
    {
        return Factory<BaseCommandReceiver, const std::string>::instance()->CreateObject(strCommandReceiver);
    }
};

template <class DerivedCommandReceiver> 
class RegisterCommandReceiverClass
{
public:
    static BaseCommandReceiver * Create()
    {
        return new DerivedCommandReceiver;
    }
    RegisterCommandReceiverClass(const std::string& strId)
    {
        Factory<BaseCommandReceiver, const std::string>::instance()->Register(strId, RegisterCommandReceiverClass::Create);
    }
};

#define CREATECOMMANDRECEIVER(CommandReceiver) BaseCommandReceiver::CreateCommandReceiver(ClassNameToString(CommandReceiver))
