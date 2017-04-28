#ifndef NEURONNETWORK_HPP
#define NEURONNETWORK_HPP

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
    void learning(const string& style);
};


#endif //NEURONNETWORK_HPP
