// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include "base/at_exit.h"
#include "gtest/include/gtest/gtest.h"

int main(int argc, wchar_t* argv[]) {
  base::AtExitManager exitMgr;

  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}
