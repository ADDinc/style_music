#include <gtest/gtest.h>
#include <common.hpp>

#define  indexNextPointerArgv 1

TEST(common, getFileListFromFile)
{
    std::vector<std::string> theresFileList ;
    getFileListFromFile ("test/filesForTest/testPath.txt", theresFileList);
    std::vector<std::string> expectFileList = {"test/filesForTest/Kany West - Power.mp3","test/filesForTest/Arctic Monkey - Old Yellow Bricks.mp3"};
    EXPECT_EQ (theresFileList, expectFileList);
}

TEST(common, fewParametrs)
{
    optind = indexNextPointerArgv;
    std::vector<std::string> outFileList;
    char *argv[] = {nullptr};
    const int result = input(1, argv, outFileList);
    EXPECT_EQ(result,-1);
}

TEST(common, fileParametrs)
{
    optind = indexNextPointerArgv;
    std::vector<std::string> outFileList;
    char paramtr[] = "test/filesForTest/Kany West - Power.mp3";
    char *argv[] = {nullptr,paramtr};
    EXPECT_EQ(input(2, argv, outFileList), 0);
    EXPECT_EQ("test/filesForTest/Kany West - Power.mp3", outFileList[0]);
}

TEST(common, DISABLED_keyDirectoryParametrs)
{
    optind = indexNextPointerArgv;
    std::vector<std::string> outFileList;
    std::vector<std::string> outResult = {"test/filesForTest/Arctic Monkey - Old Yellow Bricks.mp3", "test/filesForTest/Kany West - Power.mp3","test/filesForTest/Maroon 5 - dont wanna know.mp3"};
    char keyd[] = "-d", directory[] = "test/filesForTest/";
    char *argv[] = {nullptr, keyd, directory};
    EXPECT_EQ(input(sizeof(argv)/sizeof(argv[0]), argv, outFileList), 0);
    std::sort(outResult.begin(),outResult.end());
    std::sort(outFileList.begin(),outFileList.end());
    EXPECT_EQ(outFileList,outResult);
}

TEST(common, keyFileParametrs)
  {
    optind = indexNextPointerArgv;
    std::vector<std::string> outFileList;
    std::vector<std::string> outResultFiles = {"test/filesForTest/Kany West - Power.mp3","test/filesForTest/Arctic Monkey - Old Yellow Bricks.mp3"};
    char keyf[] = "-f", file[] = "test/filesForTest/testPath.txt";
    char *argv[] = {nullptr, keyf, file};
    EXPECT_EQ(input(sizeof(argv)/sizeof(argv[0]), argv, outFileList),0);
    EXPECT_EQ(outFileList,outResultFiles);
}

TEST(common, keyLearnParametrs)
{
    optind = indexNextPointerArgv;
    std::vector<std::string> outFileList;
    char keyf[] = "-f", file[] = "test/filesForTest/testPath.txt";
    char keyl[] = "-l", stylemusic[] = "rap";
    char *argv[] = {nullptr, keyf, file, keyl, stylemusic};
    EXPECT_EQ(input(sizeof(argv)/sizeof(argv[0]), argv, outFileList),0);
    EXPECT_EQ(stylemusic,style);
    EXPECT_TRUE(learn);
}

TEST(common, keyInfoParametrs)
{
    optind = indexNextPointerArgv;
    std::vector<std::string> outFileList;
    char keyi[] = "-i";
    char *argv[] = {nullptr, keyi};
    EXPECT_EQ(input(sizeof(argv)/sizeof(argv[0]), argv, outFileList),0);
    EXPECT_TRUE(info);
}
