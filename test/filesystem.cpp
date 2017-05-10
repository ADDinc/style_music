#include <gtest/gtest.h>
#include <filesystem.hpp>

TEST(filesystem, test_replace)
{
    std::string replaced = "Replaced";
    replace(replaced, "e", "_");
    ASSERT_EQ("R_plac_d", replaced);
    replace(replaced, "_p", "0");
    ASSERT_EQ("R0lac_d", replaced);
}
