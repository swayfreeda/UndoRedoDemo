#pragma once

#include <stack>
#include "BaseCommandManager.h"
#include "Subject.h"
#include "Singleton.h"

#define EVENT_UNDOREDOSTATECHANGED  1

class BaseCommand;

class CommandManager : public BaseCommandManager, public Subject
{
    class UndoRedoStateInspector
    {
        friend class CommandManager;

    private:
        UndoRedoStateInspector(CommandManager * pCommandManager);
        ~UndoRedoStateInspector();

    private:
        CommandManager * m_pCommandManager;
        bool m_bUndoable;
        bool m_bRedoable;
    };

    friend class Singleton<CommandManager>;

private:
    CommandManager();
	~CommandManager();
    CommandManager(const CommandManager& rhs);
    CommandManager& operator=(const CommandManager& rhs);

public:
    static CommandManager * Instance();

    bool CallCommand(BaseCommand * pCommand);
	void ClearAllCommands();
    void Undo();
    void Redo();
    bool CanUndo() const;
    bool CanRedo() const;

private:
    void PushUndoCommand(BaseCommand * pCommand);
    BaseCommand * PopUndoCommand();
    void PushRedoCommand(BaseCommand * pCommand);
    BaseCommand * PopRedoCommand();
    void DeleteUndoCommands();
    void DeleteRedoCommands();

private:
    std::stack<BaseCommand *> m_stackUndo;
    std::stack<BaseCommand *> m_stackRedo;
};

#define CALLCOMMAND(Command) CommandManager::Instance()->CallCommand(Command)
#define UNDO CommandManager::Instance()->Undo()
#define REDO CommandManager::Instance()->Redo()
#define CLEARALLCOMMANDS CommandManager::Instance()->ClearAllCommands();
#define CANUNDO CommandManager::Instance()->CanUndo()
#define CANREDO CommandManager::Instance()->CanRedo()
