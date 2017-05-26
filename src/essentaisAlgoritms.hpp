#pragma once

#include "common.hpp"

using namespace std;
using namespace essentia;
using namespace essentia::standard;

typedef vector <string> VectorPoolTags;

typedef vector <Real> VectorPoolStat;

typedef map <string, VectorPoolStat> MapMono;

typedef map <string, VectorPoolTags> MapTags;

void getMetadata(const string &audioFilename);
Pool getPoolMonoLoader(const string audioFilename);
MapMono getMapMonoLoader(Pool monoPool);