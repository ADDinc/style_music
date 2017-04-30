#pragma once
#include <string>
#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include <essentia/pool.h>

using namespace std;
using namespace essentia;
using namespace essentia::standard;

typedef vector <string> VectorPoolTags;
typedef vector <Real> VectorPoolStat;
typedef map <string, VectorPoolStat> MapMono;
typedef map <string, VectorPoolTags> MapTags;

Pool getPoolMetadataReader(const string audioFilename);
MapTags getMapMetadataReader(Pool metaPool);
Pool getPoolMonoLoader(const string audioFilename);
MapMono getMapMonoLoader(Pool monoPool);
void YamlOutputPool(const string outputFilename, Pool pool);
