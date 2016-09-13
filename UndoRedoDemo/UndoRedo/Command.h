#pragma once

#include "BaseCommand.h"

class BaseCommandReceiver;

class Command : public BaseCommand
{
public:
    Command();
    virtual ~Command();

    virtual bool Execute();
    virtual bool Unexecute();

    void SetReceiver(BaseCommandReceiver * pReceiver, bool bAutoDelete = true);

private:
    Command(const Command& rhs);
    Command& operator=(const Command& rhs);

protected:
    BaseCommandReceiver * m_pReceiver;
    bool m_bAutoDeleteReceiver;
};
