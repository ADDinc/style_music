#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include <essentia/pool.h>
#include "essentaisAlgoritms.hpp"

using namespace std;
using namespace essentia;
using namespace essentia::standard;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "ERROR: incorrect number of arguments." << endl;
        cout << "Usage: " << argv[0] << " audio_input yaml_output" << endl;
        exit(1);
    }

    string audioFilename = argv[1];
    string outputFilename = argv[2];

    essentia::init();

    Pool poolTags = getPoolMetadataReader(audioFilename);
    MapTags v2 = getMapMetadataReader(poolTags);
    cout << endl << v2 << endl;

    Pool pool = getPoolMonoLoader(audioFilename);
    MapMono v = getMapMonoLoader(pool);
    cout << endl << v << endl;

    YamlOutputPool(outputFilename, pool);

    essentia::shutdown();

    return 0;
}