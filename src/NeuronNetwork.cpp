#include "NeuronNetwork.hpp"

void NeuronNetwork::loadNeurons()
{
    ifstream File(filename, ios_base::in|ios_base::binary);
    if (File.is_open())
    {
        uint32_t len;
        while (File.read(reinterpret_cast<char*>(&len), sizeof(len)))
        {
            char *buffer = new char[len + 1];
            File.read(buffer, len);
            buffer[len] = 0;
            Neuron newNeuron(buffer);
            delete[] buffer;
            newNeuron.loadData(File);
            neurons.push_back(newNeuron);
        }
        File.close();
    }
    else
    {
        throw runtime_error("Error opening file \"" + filename + "\" for read data.");
    }
}

void NeuronNetwork::saveNeurons()
{
    ofstream File(filename, ios_base::out|ios_base::trunc|ios_base::binary);
    if (File.is_open())
    {
        for (auto& neuron : neurons)
        {
            neuron.saveData(File);
        }
        File.close();
    }
    else
    {
        throw runtime_error("Error opening file \"" + filename + "\" for write data.");
    }
}

NeuronNetwork::NeuronNetwork(const string& filename)
{
    this->filename = filename;
    loadNeurons();
}

NeuronNetwork::~NeuronNetwork()
{
    saveNeurons();
}
