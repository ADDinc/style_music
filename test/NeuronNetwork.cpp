#include <gtest/gtest.h>
#include <NeuronNetwork.hpp>
#include <filesystem.hpp>

class NeuronNetworkTest: public ::testing::Test
{
protected:
    void SetUp()
    {
        essentia::init();
        net = nullptr;
    }

    void TearDown()
    {
        essentia::shutdown();
    }

    NeuronNetwork *net;

};

TEST_F(NeuronNetworkTest, createBdNeurons)
{
    std::string filename = "NNtest.db";
    net = new NeuronNetwork(filename, false);
    EXPECT_TRUE(net != nullptr);
    try {
        MapMono map = getMapMonoLoader(getPoolMonoLoader("test/filesForTest/Kany West - Power.mp3"));
        net->learning("test", map);
    }
    catch (std::exception &ex) {
        GTEST_LOG_(WARNING) << ex.what();
    }

    delete net;
    net = nullptr;
}

TEST_F(NeuronNetworkTest, readBdNeurons)
{
    std::string filename = "NNtest.db";
    net = new NeuronNetwork(filename);
    EXPECT_TRUE(net != nullptr);
    try {
        MapMono jedi = getMapMonoLoader(getPoolMonoLoader("test/filesForTest/Kany West - Power.mp3"));
        EXPECT_GE(net->getPower(jedi)[0], 110);
    }
    catch (std::exception &ex) {
        GTEST_LOG_(WARNING) << ex.what();
    }

    delete net;
    net = nullptr;
    remove("NNtest.db");
}
