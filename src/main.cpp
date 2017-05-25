#include "filesystem.hpp"
#include "NeuronNetwork.hpp"

using namespace std;
using namespace essentia;
using namespace essentia::standard;

bool learn = false;

bool info = false;

string style;

int main(int argc, char *argv[])
{
    vector<string> files;
    if (input(argc, argv, files) == -1)
        return -1;
    if (!files.empty()) {
        essentia::init();

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
    }
    else {
        cerr << "File list is empty!" << endl << "Use: " << argv[0]
             << " <filename|-d (directory)|-f (file)> <необязательные параметры>" << endl;
        return 1;
    }
    return 0;
}
