#include "StdAfx.h"
#include "Command.h"
#include "BaseCommandReceiver.h"

RegisterCommandClass<Command> RegisterCommandClass(ClassNameToString(Command));

Command::Command(void):
m_pReceiver(NULL),
m_bAutoDeleteReceiver(true)
{
}

Command::~Command(void)
{
    if (m_bAutoDeleteReceiver && m_pReceiver)
    {
        delete m_pReceiver;
        m_pReceiver = NULL;
    }
}

bool Command::Execute()
{
    if (m_pReceiver)
    {
        return m_pReceiver->Action(false);
    }

    return false;
}

bool Command::Unexecute()
{
    if (m_pReceiver)
    {
        return m_pReceiver->Action(true);
    }

    return false;
}

void Command::SetReceiver(BaseCommandReceiver * pReceiver, bool bAutoDelete/* = true*/)
{
    m_pReceiver = pReceiver;
    m_bAutoDeleteReceiver = bAutoDelete;
}
