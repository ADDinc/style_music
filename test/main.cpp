#include <gtest/gtest.h>

bool learn = false;
bool info = false;
std::string style;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
