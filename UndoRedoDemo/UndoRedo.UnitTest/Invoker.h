#pragma once

#include <list>
#include "UndoRedo\Observer.h"
#include "gtest\gtest.h"

class Command;

class Invoker : public Observer, public ::testing::Test
{
public:
    Invoker();
    ~Invoker();

    void PushElement(int nElement);
    void PopElement();
    void ClearAllElements();
    void DisplayList() const;

    virtual bool Update(Subject* pSubject, Observer* pObserverFrom, unsigned int Event, const std::stringstream& Data);

protected:
    Command * ConstructCommand(int nElement);
    void UpdateUndoRedoState(bool bUndoable, bool bRedoable);

protected:
    std::list<int> m_listElements;
};
