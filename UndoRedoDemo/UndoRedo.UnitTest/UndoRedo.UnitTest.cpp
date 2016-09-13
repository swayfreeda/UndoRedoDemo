// UndoRedo.UnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "gtest/gtest.h"

int _tmain(int argc, _TCHAR* argv[])
{
    ::testing::InitGoogleTest(&argc, argv); 
    int nRet = RUN_ALL_TESTS(); 

    return nRet;
}
