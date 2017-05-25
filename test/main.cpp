#include <gtest/gtest.h>

bool learn = false;

bool info = false;

std::string style;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(print_time) = true;
    testing::GTEST_FLAG(also_run_disabled_tests) = true; //--gtest_also_run_disabled_tests
    return RUN_ALL_TESTS();
}
