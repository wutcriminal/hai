#include "main.h"
#include "iostream"
#define GTEST_LANG_CXX11 1

#pragma comment(lib, "googletest_v141.lib")

#include "gtest/gtest.h"
using namespace std;

TEST(BUTTONTest, BTest) {
    BUTTON btn(750, 18, 150, 40, _T("ÎÒÊÇÄãµù"), func_test);
    EXPECT_EQ(btn.paint(),1);
}

TEST(WORLDTest,WTest) {
    WORLD wld;
    EXPECT_EQ(wld.PaintWorld(), 1);
}

TEST(EVOTest,ETest) {
    WORLD wld;
    wld.Evolution();
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);


    return RUN_ALL_TESTS();
}

