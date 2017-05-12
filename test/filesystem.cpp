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
  std::vector<std::string> regexMask;
  std::vector<std::string> outRegeMask = {{"*.flac"},{"*.mp3"},{"*.m4a"}};
  std::string strMask = "*.flac|*.mp3|*.m4a";
  split(strMask, "|", regexMask);
  unsigned int vector_size_regexMask = regexMask.size();
  unsigned int vector_size_outRegexMask = outRegeMask.size();
  EXPECT_EQ(vector_size_regexMask, vector_size_outRegexMask);
  //EXPECT_DEATH({split(strMask, "|", regexMask);},"");
}

TEST(expectTrueFalseTest,testDirectoryExist)
{
  std::string directory = "";
  EXPECT_TRUE(directoryExist(directory));
  directory = "no empty";
  EXPECT_FALSE(directoryExist(directory));
}

class createDirectoryTest : public ::testing::Test
{
    public:
        virtual ~createDirectoryTest() {rmdir("temp");}
    protected:
        virtual void SetUp()
        {
            // не должен работать когда есть ~/#/%/&/*/{}/\/:/<>/?/+/|/""/_/./_vti_
        }
        virtual void TearDown()
        {
          rmdir("temp");
        }
};

TEST(createDirectoryTest ,testCreateDirectory)
{
  std::string directory = "temp";
  EXPECT_TRUE(createDirectory(directory));
  EXPECT_FALSE(createDirectory(directory));
  rmdir("temp");
}

TEST(expectFalseTrueTest,testFileExist)
{
  std::string filemane = "Rihana.mp3";
  EXPECT_FALSE(fileExist(filemane));
  filemane = "KanyWast.mp3";
  EXPECT_TRUE(fileExist(filemane));
}

TEST(expectFalseTrueTes,testCheckFileMask)
{
  std::vector<std::string> outRegeMask = getRegexMask("*.flac|*.mp3|*.m4a");
  std::string filemane = "KanyWast.mp3";
  EXPECT_TRUE(checkFileMask(outRegeMask, filemane));
}
