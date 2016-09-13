#include "StdAfx.h"
#include <iostream>
#include "Invoker.h"
#include "UndoRedo\CommandManager.h"
#include "UndoRedo\Command.h"
#include "UndoRedo\MacroCommand.h"
#include "MockCommandReceiver.h"
#include "MockCommand.h"

Invoker::Invoker()
{
    Observe(CommandManager::Instance(), EVENT_UNDOREDOSTATECHANGED);

    UpdateUndoRedoState(CommandManager::Instance()->CanUndo(), CommandManager::Instance()->CanRedo());
}

Invoker::~Invoker()
{
    UnObserve(CommandManager::Instance(), EVENT_UNDOREDOSTATECHANGED);
}

void Invoker::UpdateUndoRedoState(bool bUndoable, bool bRedoable)
{
    std::cout << "Undoable : " << (bUndoable?"True":"False") << "\n";
    std::cout << "Redoable : " << (bRedoable?"True":"False") << "\n\n";
}

bool Invoker::Update(Subject* pSubject, Observer* pObserverFrom, unsigned int Event, const std::stringstream& Data)
{
    std::stringstream data(Data.str().c_str());

    if (Event == EVENT_UNDOREDOSTATECHANGED)
    {
        bool bUndoable;
        data >> bUndoable;
        char c;
        data >> c;
        bool bRedoable;
        data >> bRedoable;

        UpdateUndoRedoState(bUndoable, bRedoable);
    }
    return true;
}

Command * Invoker::ConstructCommand(int nElement)
{
    MockCommandReceiver * pReceiver = (MockCommandReceiver *)CREATECOMMANDRECEIVER(MockCommandReceiver);
    Command * pCommand = (Command *)CREATECOMMAND(Command);
    pCommand->SetReceiver(pReceiver);
    pReceiver->PrepareData(this, nElement);
    return pCommand;
}

void Invoker::PushElement(int nElement)
{
    m_listElements.push_back(nElement);
}

void Invoker::PopElement()
{
    m_listElements.pop_back();
}

void Invoker::ClearAllElements()
{
    m_listElements.clear();
}

void Invoker::DisplayList() const
{
    if (m_listElements.size() == 0)
    {
        std::cout << "List: <Empty>";
    }
    else
    {
        std::cout << "List: ";
        int i = 0;
        std::list<int>::const_iterator iter;
        for (iter = m_listElements.begin(); i < 10 && iter != m_listElements.end() ; i++, iter++)
        {
            std::cout << " " << *iter;
        }
        if (iter != m_listElements.end())
        {
            std::cout << " and other " << m_listElements.size()-10 << " elements...";
        }
    }
    std::cout << "\n\n";
}

TEST_F(Invoker, TestUndoRedoFramework)
{
    std::cout << "----- Test simple command and undo/redo -----\n\n";

    std::cout << "Execute\n";
    int nElement1 = 1;
    CALLCOMMAND(ConstructCommand(nElement1));
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);
    int expect = 1;
    int actual = m_listElements.size();
    ASSERT_EQ(expect, actual);
    expect = nElement1;
    std::list<int>::const_iterator iter = m_listElements.begin();
    actual = *iter;
    ASSERT_EQ(expect, actual);

    std::cout << "Execute\n";
    int nElement2 = 2;
    CALLCOMMAND(ConstructCommand(nElement2));
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);
    expect = 2;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);
    expect = nElement1;
    iter = m_listElements.begin();
    actual = *iter;
    ASSERT_EQ(expect, actual);
    expect = nElement2;
    actual = *(++iter);
    ASSERT_EQ(expect, actual);

    std::cout << "Undo\n";
    UNDO;
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_TRUE(CANREDO);
    expect = 1;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);

    std::cout << "Redo\n";
    REDO;
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);
    expect = 2;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);
    expect = nElement1;
    iter = m_listElements.begin();
    actual = *iter;
    ASSERT_EQ(expect, actual);
    expect = nElement2;
    actual = *(++iter);
    ASSERT_EQ(expect, actual);

    std::cout << "Undo twice\n";
    UNDO;
    UNDO;
    DisplayList();

    ASSERT_FALSE(CANUNDO);
    ASSERT_TRUE(CANREDO);
    expect = 0;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);

    std::cout << "Redo twice\n";
    REDO;
    REDO;
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);
    expect = 2;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);
    expect = nElement1;
    iter = m_listElements.begin();
    actual = *iter;
    ASSERT_EQ(expect, actual);
    expect = nElement2;
    actual = *(++iter);
    ASSERT_EQ(expect, actual);

    std::cout << "----- Test clear all commands -----\n\n";

    std::cout << "Clear all commands\n";
    CLEARALLCOMMANDS;

    ASSERT_FALSE(CANUNDO);
    ASSERT_FALSE(CANREDO);

    std::cout << "----- Test macro command -----\n\n";

    CLEARALLCOMMANDS;
    ClearAllElements();

    std::cout << "Execute\n";
    MacroCommand * pMacroCommand = (MacroCommand *)CREATECOMMAND(MacroCommand);
    int nElement3 = 3;
    pMacroCommand->AddCommand(ConstructCommand(nElement3));
    int nElement4 = 4;
    pMacroCommand->AddCommand(ConstructCommand(nElement4));
    int nElement5 = 5;
    pMacroCommand->AddCommand(ConstructCommand(nElement5));
    CALLCOMMAND(pMacroCommand);
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);
    expect = 3;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);

    std::cout << "Undo\n";
    UNDO;
    DisplayList();

    ASSERT_FALSE(CANUNDO);
    ASSERT_TRUE(CANREDO);
    expect = 0;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);

    std::cout << "Redo\n";
    REDO;
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);
    expect = 3;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);
    std::vector<int> vecElements;
    vecElements.push_back(nElement3);
    vecElements.push_back(nElement4);
    vecElements.push_back(nElement5);
    int i = 0;
    for (iter = m_listElements.begin(); iter != m_listElements.end(); iter++, i++)
    {
        expect = vecElements[i];
        actual = *iter;
        ASSERT_EQ(expect, actual);
    }

    std::cout << "----- Test command called after undo -----\n\n";

    CLEARALLCOMMANDS;
    ClearAllElements();

    std::cout << "Execute\n";
    int nElement6 = 6;
    CALLCOMMAND(ConstructCommand(nElement6));
    DisplayList();
    std::cout << "Undo\n";
    UNDO;
    DisplayList();
    std::cout << "Execute\n";
    int nElement7 = 7;
    CALLCOMMAND(ConstructCommand(nElement7));
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);
    expect = 1;
    actual = m_listElements.size();
    ASSERT_EQ(expect, actual);
    expect = nElement7;
    iter = m_listElements.begin();
    actual = *iter;
    ASSERT_EQ(expect, actual);

    std::cout << "----- Test failed command and undo/redo -----\n\n";

    CLEARALLCOMMANDS;
    ClearAllElements();

    MockCommand * pMockCommand = (MockCommand *)CREATECOMMAND(MockCommand);
    pMockCommand->PrepareData(true);
    std::cout << "Execute\n";
    CALLCOMMAND(pMockCommand);
    std::cout << "Undo\n";
    UNDO;
    std::cout << "Redo\n";
    REDO;

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);

    pMockCommand->PrepareData(false);
    std::cout << "Undo\n";
    UNDO;

    ASSERT_FALSE(CANUNDO);
    ASSERT_FALSE(CANREDO);

    pMockCommand = (MockCommand *)CREATECOMMAND(MockCommand);
    pMockCommand->PrepareData(true);
    std::cout << "Execute\n";
    CALLCOMMAND(pMockCommand);
    std::cout << "Undo\n";
    UNDO;

    ASSERT_FALSE(CANUNDO);
    ASSERT_TRUE(CANREDO);

    pMockCommand->PrepareData(false);
    std::cout << "Redo\n";
    REDO;

    ASSERT_FALSE(CANUNDO);
    ASSERT_FALSE(CANREDO);

    std::cout << "----- Test lots of commands and undo/redo -----\n\n";

    CLEARALLCOMMANDS;

    const int nCount = 300;
    for (i = 0; i < nCount; i++)
    {
        CALLCOMMAND(ConstructCommand(i));
    }
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);

    for (i = 0; i < nCount; i++)
    {
        UNDO;
    }
    DisplayList();

    ASSERT_FALSE(CANUNDO);
    ASSERT_TRUE(CANREDO);

    for (i = 0; i < nCount; i++)
    {
        REDO;
    }
    DisplayList();

    ASSERT_TRUE(CANUNDO);
    ASSERT_FALSE(CANREDO);

    CLEARALLCOMMANDS;

    ASSERT_FALSE(CANUNDO);
    ASSERT_FALSE(CANREDO);
}
