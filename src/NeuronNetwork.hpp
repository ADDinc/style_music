#pragma once

#include "neuron.hpp"

class NeuronNetwork
{
private:
    std::vector<Neuron> neurons;
    std::string filename;

    void loadNeurons();
    void saveNeurons();
public:
    NeuronNetwork(const string& filename, bool load);
    ~NeuronNetwork();
    void learning(const string& style, MapMono& map);
    std::vector<double> getPower(MapMono& map);
};
