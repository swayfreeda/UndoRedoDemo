#include "StdAfx.h"
#include <iostream>
#include "MockCommandReceiver.h"
#include "Invoker.h"

RegisterCommandReceiverClass<MockCommandReceiver> RegisterCommandReceiverClass(ClassNameToString(MockCommandReceiver));

MockCommandReceiver::MockCommandReceiver():
m_pInvoker(NULL),
m_nData(0)
{
}

MockCommandReceiver::~MockCommandReceiver()
{
}

bool MockCommandReceiver::Action(bool bUndo)
{
    if (bUndo)
    {
        if (!m_pInvoker)
        {
            return false;
        }
        else
        {
            m_pInvoker->PopElement();
        }
    }
    else
    {
        if (!m_pInvoker)
        {
            return false;
        }
        else
        {
            m_pInvoker->PushElement(m_nData);
        }
    }

    return true;
}

void MockCommandReceiver::PrepareData(Invoker * pInvoker, int nParameter)
{
    m_pInvoker = pInvoker;
    m_nData = nParameter;
}
