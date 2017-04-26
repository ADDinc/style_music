#include "neuron.hpp"

Neuron::Neuron(const string& style) : style(style)
{
    _data = new InputData[20];
    loadData();
}

void Neuron::loadData()
{
    ifstream File(style, ios_base::in);
    if (File.is_open())
    {
        File.close();
    }
}

void Neuron::saveData()
{
    ofstream File(style, ios_base::out);
    if (File.is_open())
    {
        File.close();
    }
}

const string& Neuron::getStyleName() const
{
    return style;
}

Neuron::~Neuron()
{
    saveData();
    delete[] _data;
}
