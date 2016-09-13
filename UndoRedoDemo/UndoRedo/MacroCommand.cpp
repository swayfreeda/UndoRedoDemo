#include "StdAfx.h"
#include <algorithm>
#include "MacroCommand.h"
#include "Util.h"

RegisterCommandClass<MacroCommand> RegisterCommandClass(ClassNameToString(MacroCommand));

MacroCommand::MacroCommand()
{
}

MacroCommand::~MacroCommand()
{
    ContainerDeleter<std::vector<BaseCommand *>>(m_vecCommands);
}

bool MacroCommand::Execute()
{
    for (unsigned int i = 0; i < m_vecCommands.size(); i++)
    {
        BaseCommand * pCommand = m_vecCommands[i];
        if (!pCommand->Execute())
        {
            return false;
        }
    }
    return true;
}

bool MacroCommand::Unexecute()
{
    for (unsigned int i = m_vecCommands.size(); i > 0; i--)
    {
        BaseCommand * pCommand = m_vecCommands[i-1];
        if (!pCommand->Unexecute())
        {
            return false;
        }
    }
    return true;
}

void MacroCommand::AddCommand(BaseCommand * pCommand)
{
    if (pCommand)
    {
        m_vecCommands.push_back(pCommand);
    }
}

void MacroCommand::DeleteCommand(BaseCommand * pCommand)
{
    if (pCommand)
    {
        m_vecCommands.erase(std::remove(m_vecCommands.begin(), m_vecCommands.end(), pCommand));
    }
}
