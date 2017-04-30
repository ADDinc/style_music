#include "filesystem.hpp"
#include "NeuronNetwork.hpp"

using namespace std;
using namespace essentia;
using namespace essentia::standard;

int main(int argc, char* argv[]) {
    essentia::init();
    vector<string> files;
    
    try
    {
        vector<string> mask = getRegexMask("*.flac|*.mp3|*.m4a");
        getFileList(argv[1], files, mask, true);
    }
    catch(exception &ex)
    {
        exceptionPrint(ex, "main (get file list)");
    }
    Pool poolTags;
    MapTags v2;
    Pool pool;
    MapMono v;
    string style = argv[2];
    
    try
    {
        //NeuronNetwork neuNtw("NN.db", false); // ничего не загружается создается чистая
        NeuronNetwork neuNtw("NN.db", true); // загрузка
        for(auto f : files)
        {
            //Neuron neu(style);
            v2 = getMapMetadataReader(getPoolMetadataReader(f));
            v = getMapMonoLoader(getPoolMonoLoader(f));
            //cout << v2["title"] << "::" << v << endl;

            //neu.setupData(v);
            //neu.print();
            neuNtw.learning(style, v);
        }
    }
    catch(exception &ex)
    {
        exceptionPrint(ex, "main (learning)");
    }

    essentia::shutdown();
    return 0;
}
