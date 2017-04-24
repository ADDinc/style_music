#ifndef NEURON_HPP
#define NEURON_HPP

//#pragma once
#include <vector>
#include <fstream>

typedef struct {
    double max;
    double mean;
    double min;
    double var;
} InputData;

class Neuron
{
    using namespace std;
private:
    InputData _data[];
    string style;
    double weight;
    double threshold;
public:
    Neuron(const string& style) : style(style)
    {
        _data = new InputData[20];
        loadData();
    }

    bool saveData()
    {
        ifstream File(style, ios_base::in);
        if (File.is_open())
        {
            File.close();
        }
    }

    void loadData()
    {
        ofstream File(style, ios_base::out);
        if (File.is_open())
        {
            File.close();
        }
    }

    ~Neuron()
    {
        saveData();
        delete[] _data;
    }
};

class NeuronNetwork
{
private:
    std::vector<Neuron> neurons;
public:
    NeuronNetwork()
    {

    }

    ~NeuronNetwork()
    {

    }
};

#endif //NEURON_HPP
