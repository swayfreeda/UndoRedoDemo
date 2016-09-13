#pragma once

class BaseCommand;

class BaseCommandManager
{
public:
    virtual ~BaseCommandManager() {}
    virtual bool CallCommand(BaseCommand * pCommand) = 0;
    virtual void ClearAllCommands() = 0;
    virtual void Undo() = 0;
    virtual void Redo() = 0;
    virtual bool CanUndo() const = 0;
    virtual bool CanRedo() const = 0;
};
