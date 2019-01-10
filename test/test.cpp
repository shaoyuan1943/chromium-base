// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include "base/at_exit.h"
#include "gtest/include/gtest/gtest.h"

#pragma warning(disable:4251)

int main(int argc, char* argv[]) {
  base::AtExitManager exitMgr;


  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}
