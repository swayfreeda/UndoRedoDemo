#pragma once

#include <vector>
#include "BaseCommand.h"

class MacroCommand : public BaseCommand
{
public:
    MacroCommand();
    ~MacroCommand();

    virtual bool Execute();
    virtual bool Unexecute();

    void AddCommand(BaseCommand * pCommand);
    void DeleteCommand(BaseCommand * pCommand);

private:
    MacroCommand(const MacroCommand& rhs);
    MacroCommand& operator=(const MacroCommand& rhs);

private:
    std::vector<BaseCommand *> m_vecCommands;
};
