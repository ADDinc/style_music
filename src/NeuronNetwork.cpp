#include <algorithm>
#include "NeuronNetwork.hpp"
#include "filesystem.hpp"

void NeuronNetwork::loadNeurons()
{
    if (!directoryExist(filename.substr(0, filename.find_last_of("/")+1)))
	if (!createDirectory(filename.substr(0, filename.find_last_of("/")+1)))
           throw runtime_error("Directory database is missing");
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
        if (fileExist(filename))
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

NeuronNetwork::NeuronNetwork(const string& filename, bool load)
{
    this->filename = filename;
    if (load) {
        loadNeurons();
    }
}

void NeuronNetwork::learning(const string &style, MapMono &data)
{
    auto it = std::find_if(neurons.begin(), neurons.end(), [&](const Neuron& d) {return (style == d.getStyleName());});
    if (it == neurons.end())
    {
        neurons.push_back(Neuron(style));
        it = --neurons.end();
    }
    it->setupData(data);
}

NeuronNetwork::~NeuronNetwork()
{
    try
    {
        saveNeurons();
    }
    catch(exception &ex)
    {
        exceptionPrint(ex, "NetworkDestruct (save)");
    }
}
