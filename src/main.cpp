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
    vector <string> files;
    if (input(argc, argv, files) == -1)
        return -1;
    if (!files.empty()) {
        essentia::init();

        try {
            NeuronNetwork neuNtw("NN.db");
            vector<double> power;
            for (auto &file : files) {
                if (info)
                    getMetadata(file);
                MapMono mapMonoLoader = getMapMonoLoader(getPoolMonoLoader(file));
                if (learn) {
                    neuNtw.learning(style, mapMonoLoader);
                }
                else {
                    cout << CYAN << getFilenameFromFilePath(file) << ": " RESET;
                    if (!neuNtw.getStyles(mapMonoLoader)) {
                        cout << "none" << endl;
                        break;
                    }
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
