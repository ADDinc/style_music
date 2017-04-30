#include "filesystem.hpp"
#include <unistd.h>
#include "NeuronNetwork.hpp"

using namespace std;
using namespace essentia;
using namespace essentia::standard;

int main(int argc, char *argv[])
{

    int rez = 0;
    string dir, style;
    bool learn = false;
//	opterr=0;
    while ((rez = getopt(argc, argv, "d:l:")) != -1) {
        switch (rez) {
            case 'd': {
                printf("found argument \"d = %s\".\n", optarg);
                dir = optarg;
                break;
            }
            case 'l': {
                printf("found argument \"l = %s\".\n", optarg);
                style = optarg;
                learn = true;
                break;
            }
            case '?':
                printf("Error found !\n");
                break;
        };
    };
    cout << dir << "  " << style << endl;
    essentia::init();
    vector <string> files;

    try {
        vector <string> mask = getRegexMask("*.flac|*.mp3|*.m4a");
        getFileList(dir, files, mask, true);
    }
    catch (exception &ex) {
        exceptionPrint(ex, "main (get file list)");
    }
    Pool poolTags;
    MapTags v2;
    Pool pool;
    MapMono v;

    try {
        //NeuronNetwork neuNtw("NN.db", false); // ничего не загружается создается чистая
        NeuronNetwork neuNtw("NN.db", true); // загрузка
        vector<double> power;
        for (auto f : files) {
            //Neuron neu(style);
            v2 = getMapMetadataReader(getPoolMetadataReader(f));
            v = getMapMonoLoader(getPoolMonoLoader(f));
            //cout << v2["title"] << "::" << v << endl;

            //neu.setupData(v);
            //neu.print();
            if (learn) {
                neuNtw.learning(style, v);
            }
            else {
                neuNtw.printPower(v);
            }
        }
    }
    catch (exception &ex) {
        exceptionPrint(ex, "main (learning)");
    }

    essentia::shutdown();
    return 0;
}
