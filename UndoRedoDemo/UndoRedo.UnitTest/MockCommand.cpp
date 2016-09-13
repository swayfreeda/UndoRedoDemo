#include "StdAfx.h"
#include <iostream>
#include "MockCommand.h"

RegisterCommandClass<MockCommand> RegisterCommandClass(ClassNameToString(MockCommand));

MockCommand::MockCommand():
m_bReturnTrue(true)
{
}

MockCommand::~MockCommand()
{
}

bool MockCommand::Execute()
{
    // �ڴ����������ִ�д���
    std::cout << "Mock command is executing. Return " << (m_bReturnTrue?"true":"false") << ".\n\n";
    return m_bReturnTrue;
}

bool MockCommand::Unexecute()
{
    // �ڴ���������ĳ�������
    std::cout << "Mock command is unexecuting. Return " << (m_bReturnTrue?"true":"false") << ".\n\n";
    return m_bReturnTrue;
}

void MockCommand::PrepareData(bool bReturnTrue)
{
    m_bReturnTrue = bReturnTrue;
}
