#include "neuron.hpp"

Neuron::Neuron(const string& style) : style(style)
{
    _data = new InputData[20];
    weight = new InputData[20];
}

void Neuron::loadData(ifstream& in)
{
    in.read(reinterpret_cast<char*>(_data), sizeof(InputData[20]));
    in.read(reinterpret_cast<char*>(weight), sizeof(InputData[20]));
    in.read(reinterpret_cast<char*>(&countLearn), sizeof(countLearn));
}

void Neuron::saveData(ofstream& out)
{
    uint32_t len = style.length();
    out.write(reinterpret_cast<char*>(&len), sizeof(len));
    out.write(style.c_str(), len);
    out.write(reinterpret_cast<char*>(_data), sizeof(InputData[20]));
    out.write(reinterpret_cast<char*>(weight), sizeof(InputData[20]));
    out.write(reinterpret_cast<char*>(&countLearn), sizeof(countLearn));
}

const string& Neuron::getStyleName() const
{
    return style;
}

Neuron::~Neuron()
{
    delete[] _data;
    delete[] weight;
}
