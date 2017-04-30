#pragma once

#include "neuron.hpp"

class NeuronNetwork
{
private:
    std::string filename;

    void loadNeurons();
    void saveNeurons();
public:
    std::vector<Neuron> neurons;
    NeuronNetwork(const string& filename, bool load);
    ~NeuronNetwork();
    void learning(const string& style);
};
