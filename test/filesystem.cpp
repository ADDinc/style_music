#include <gtest/gtest.h>
#include <filesystem.hpp>


TEST(filesystem, testReplace)
{
    std::string replaced = "Replaced";
    replace(replaced, "e", "_");
    ASSERT_EQ("R_plac_d", replaced);
    replace(replaced, "_p", "0");
    ASSERT_EQ("R0lac_d", replaced);
}

TEST(filesystem, testSplit)
{
    std::string splited = "Spl:it";
    std::vector<std::string> out, res{"Spl", "it"};
    split(splited, ":", out);
    ASSERT_EQ(res.size(), out.size());
    EXPECT_EQ(res, out);
}

TEST(filesystem, testMask)
{
    std::vector<std::string> regexMask = getRegexMask("*.flac|*.mp3|*.m4a");
    std::vector<std::string> outRegexMask = {".*\\.flac", ".*\\.mp3", ".*\\.m4a"};
    EXPECT_EQ(regexMask.size(), outRegexMask.size());
    EXPECT_EQ(regexMask, outRegexMask);
}

TEST(filesystem, testDirectoryExist)
{
    EXPECT_TRUE(directoryExist("test"));
    EXPECT_FALSE(directoryExist("no empty"));
}

TEST(filesystem, testCreateDirectory)
{
    std::string directory = "temp";
    EXPECT_TRUE(createDirectory(directory));
    EXPECT_FALSE(createDirectory(directory));
    rmdir(directory.c_str());
}

TEST(filesystem, testFileExist)
{
    EXPECT_FALSE(fileExist("Rihana.mp3"));
    EXPECT_TRUE(fileExist("test/filesForTest/Kany West - Power.mp3"));
}

TEST(filesystem, testCheckFileMask)
{
    EXPECT_TRUE(checkFileMask(getRegexMask("*.flac|*.mp3|*.m4a"), "Hello.mp3"));
}
