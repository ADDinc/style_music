#include "filesystem.hpp"
#include <unistd.h>
#include "NeuronNetwork.hpp"

using namespace std;
using namespace essentia;
using namespace essentia::standard;

int main(int argc, char *argv[])
{
    if (argc == 1) {
        cout << "Use: " << argv[0] << " <filename|-d (directory)|-f (file)> <необязательные параметры>" << endl;
        return 1;
    }

    int rez = 0;
    string dir, style;
    bool learn = false;
    while ((rez = getopt(argc, argv, "d:l:")) != -1) {
        switch (rez) {
        case 'd':
            printf("found argument \"d = %s\".\n", optarg);
            dir = optarg;
            break;
        case 'l':
            printf("found argument \"l = %s\".\n", optarg);
            style = optarg;
            stringTolower(style);
            learn = true;
            break;
        case '?':
            printf("Error found !\n");
            break;
        };
    };
    essentia::init();
    vector <string> files;

    try {
        vector <string> mask = getRegexMask("*.flac|*.mp3|*.m4a");
        getFileList(dir, files, mask);
    }
    catch (exception &ex) {
        exceptionPrint(ex, "main (get file list)");
    }
    MapTags v2;
    MapMono v;

    try {
        NeuronNetwork neuNtw("NN.db"); // загрузка
        vector<double> power;
        for (auto &f : files) {
            v2 = getMapMetadataReader(getPoolMetadataReader(f));
            v = getMapMonoLoader(getPoolMonoLoader(f));
            if (learn) {
                neuNtw.learning(style, v);
            } else {
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
