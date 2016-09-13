#pragma once

#include "UndoRedo\BaseCommand.h"

class MockCommand : public BaseCommand
{
public:
    MockCommand();
    virtual ~MockCommand();

    virtual bool Execute();
    virtual bool Unexecute();

    void PrepareData(bool bReturnTrue);

private:
    bool m_bReturnTrue;
};
