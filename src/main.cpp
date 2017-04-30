#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include <essentia/pool.h>
#include "essentaisAlgoritms.hpp"
#include "filesystem.hpp"
#include "NeuronNetwork.hpp"

using namespace std;
using namespace essentia;
using namespace essentia::standard;

int main(int argc, char* argv[]) {
    essentia::init();

    vector<string> mask = getRegexMask("*.flac|*.mp3|*.m4a");
    vector<string> files;

    getFileList(argv[1], files, mask, true);
    Pool poolTags;
    MapTags v2;
    Pool pool;
    MapMono v;
    string style = argv[2];
    NeuronNetwork neuNtw("NN.db", false); // ничего не загружается создается чистая
    //NeuronNetwork neuNtw("NN.db", true); // загрузка
    
    try
    {
        for(auto f : files)
        {
            Neuron neu(style);
            v2 = getMapMetadataReader(getPoolMetadataReader(f));
            v = getMapMonoLoader(getPoolMonoLoader(f));
            cout << v2["title"] << "::" << v << endl;

            neu.setupData(v);
            neu.print();
            neuNtw.neurons.push_back(neu);
        }
    }
    catch(exception &ex)
    {
        exceptionPrint(ex);
    }

    essentia::shutdown();
    return 0;
}
