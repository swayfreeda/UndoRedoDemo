#include "StdAfx.h"
#include "CommandManager.h"
#include "BaseCommand.h"

CommandManager::UndoRedoStateInspector::UndoRedoStateInspector(CommandManager * pCommandManager):
m_pCommandManager(pCommandManager),
m_bUndoable(pCommandManager->CanUndo()),
m_bRedoable(pCommandManager->CanRedo())
{
}

CommandManager::UndoRedoStateInspector::~UndoRedoStateInspector()
{
    if (m_bUndoable != m_pCommandManager->CanUndo() || m_bRedoable != m_pCommandManager->CanRedo())
    {
        std::stringstream ssData;
        ssData << m_pCommandManager->CanUndo();
        ssData << ',';
        ssData << m_pCommandManager->CanRedo();
        m_pCommandManager->Notify(NULL, EVENT_UNDOREDOSTATECHANGED, ssData);
    }
}

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
    ClearAllCommands();
}

CommandManager * CommandManager::Instance()
{
    return Singleton<CommandManager>::Instance();
}

bool CommandManager::CallCommand(BaseCommand * pCommand)
{
    UndoRedoStateInspector si(this);

    if (pCommand)
    {
        if (pCommand->Execute())
        {
            PushUndoCommand(pCommand);
            DeleteRedoCommands();
            return true;
        }
        else
        {
            delete pCommand;
        }
    }

    return false;
}

void CommandManager::ClearAllCommands()
{
    UndoRedoStateInspector si(this);

    DeleteUndoCommands();
    DeleteRedoCommands();
}

void CommandManager::Undo()
{
    UndoRedoStateInspector si(this);

    BaseCommand * pCommand = PopUndoCommand();
    if (pCommand)
    {
        if (pCommand->Unexecute())
        {
            PushRedoCommand(pCommand);
        }
        else
        {
            delete pCommand;
        }
    }
}

void CommandManager::Redo()
{
    UndoRedoStateInspector si(this);

    BaseCommand * pCommand = PopRedoCommand();
    if (pCommand)
    {
        if (pCommand->Execute())
        {
            PushUndoCommand(pCommand);
        }
        else
        {
            delete pCommand;
        }
    }
}

bool CommandManager::CanUndo() const
{
    return !m_stackUndo.empty();
}

bool CommandManager::CanRedo() const
{
    return !m_stackRedo.empty();
}

void CommandManager::PushUndoCommand(BaseCommand * pCommand)
{
    if (pCommand)
    {
        m_stackUndo.push(pCommand);
    }
}

BaseCommand * CommandManager::PopUndoCommand()
{
    BaseCommand * pCommand = NULL;
    if (!m_stackUndo.empty())
    {
        pCommand = m_stackUndo.top();
        m_stackUndo.pop();
    }
    return pCommand;
}

void CommandManager::PushRedoCommand(BaseCommand * pCommand)
{
    if (pCommand)
    {
        m_stackRedo.push(pCommand);
    }
}

BaseCommand * CommandManager::PopRedoCommand()
{
    BaseCommand * pCommand = NULL;
    if (!m_stackRedo.empty())
    {
        pCommand = m_stackRedo.top();
        m_stackRedo.pop();
    }
    return pCommand;
}

void CommandManager::DeleteUndoCommands()
{
    while (!m_stackUndo.empty())
    {
        delete m_stackUndo.top();
        m_stackUndo.pop();
    }
}

void CommandManager::DeleteRedoCommands()
{
    while (!m_stackRedo.empty())
    {
        delete m_stackRedo.top();
        m_stackRedo.pop();
    }
}
