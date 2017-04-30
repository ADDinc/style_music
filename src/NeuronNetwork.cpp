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

std::vector<double> NeuronNetwork::getPower(MapMono& map)
{
    std::vector<double> neuronPower(neurons.size());
    std::vector<MapMono> v;
    for(unsigned int k = 0; k < neuronPower.size(); k++){
        neuronPower[k] = 0;
    }
    for(auto& neuron : neurons){
        v.push_back(neuron.getNeuronDiff(map));
    }
    double dvar, dvar2, dmean, dmean2;
    for(unsigned int j = 0; j < 13; j++) {
        for(unsigned int i = 0; i < v.size(); i++){
            dvar = v[i]["lowlevel.mfcc.dvar"][j];
            dvar2 = v[i]["lowlevel.mfcc.dvar2"][j];
            dmean = v[i]["lowlevel.mfcc.dmean"][j];
            dmean2 = v[i]["lowlevel.mfcc.dmean2"][j];
            if (dmean - v[i]["lowlevel.mfcc.mean"][j] > 0) {
                neuronPower[i] += 2;
            }
            else if (dmean2 - v[i]["lowlevel.mfcc.mean"][j] > 0) {
                neuronPower[i] += 1;
            } else {
                int min = 0;
                for(unsigned int t = 1; t < neuronPower.size(); t++){
                    if(v[min]["lowlevel.mfcc.mean"][j] > v[t]["lowlevel.mfcc.mean"][j])
                        min = t;
                }
                neuronPower[min] += 0.5;
            }

            if(dmean - v[i]["lowlevel.mfcc.max"][j] > 0){
                neuronPower[i] += 2;
            } else if(dmean2 - v[i]["lowlevel.mfcc.max"][j] > 0){
                neuronPower[i] += 1;
            } else {
                int min = 0;
                for(unsigned int t = 1; t < neuronPower.size(); t++){
                    if(v[min]["lowlevel.mfcc.max"][j] > v[t]["lowlevel.mfcc.max"][j])
                        min = t;
                }
                neuronPower[min] += 0.5;
            }

            if(dmean - v[i]["lowlevel.mfcc.median"][j] > 0){
                neuronPower[i] += 2;
            } else if(dmean2 - v[i]["lowlevel.mfcc.median"][j] > 0){
                neuronPower[i] += 1;
            } else {
                int min = 0;
                for(unsigned int t = 1; t < neuronPower.size(); t++){
                    if(v[min]["lowlevel.mfcc.median"][j] > v[t]["lowlevel.mfcc.median"][j])
                        min = t;
                }
                neuronPower[min] += 0.5;
            }

            if(dmean - v[i]["lowlevel.mfcc.min"][j] > 0){
                neuronPower[i] += 2;
            } else if(dmean2 - v[i]["lowlevel.mfcc.min"][j] > 0){
                neuronPower[i] += 1;
            } else {
                int min = 0;
                for(unsigned int t = 1; t < neuronPower.size(); t++){
                    if(v[min]["lowlevel.mfcc.min"][j] > v[t]["lowlevel.mfcc.min"][j])
                        min = t;
                }
                neuronPower[min] += 0.5;
            }

            if(dvar - v[i]["lowlevel.mfcc.var"][j] > 0){
                neuronPower[i] += 2;
            } else if(dvar2 - v[i]["lowlevel.mfcc.var"][j] > 0){
                neuronPower[i] += 1;
            } else {
                int min = 0;
                for(unsigned int t = 1; t < neuronPower.size(); t++){
                    if(v[min]["lowlevel.mfcc.var"][j] > v[t]["lowlevel.mfcc.var"][j])
                        min = t;
                }
                neuronPower[min] += 0.5;
            }
        }
    }
    return neuronPower;
}

NeuronNetwork::~NeuronNetwork()
{
    saveNeurons();
}
