#pragma once

#include "UndoRedo\BaseCommandReceiver.h"

class Invoker;

class MockCommandReceiver : public BaseCommandReceiver
{
public:
    MockCommandReceiver();
    ~MockCommandReceiver();

    virtual bool Action(bool bUndo);

    void PrepareData(Invoker * pInvoker, int nParameter);

public:
    int m_nData;
    Invoker * m_pInvoker;
};
