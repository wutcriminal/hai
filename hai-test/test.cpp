#include "pch.h"
#include"../hai/main.cpp"
TEST(BUTTONTEST, BTest) {
    BUTTON tes(750, 18, 150, 40, _T("ÎÒÊÇÄãµù"), func_test);
    EXPECT_EQ(750, tes.x) << "caonima";
}