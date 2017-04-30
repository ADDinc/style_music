#include "neuron.hpp"

Neuron::Neuron(const string& style) : style(style)
{
    _data = new InputData[13];
    weight = new InputData[13];
    countLearn = 0;
}

Neuron::Neuron(const Neuron& copy) : style(copy.style), threshold(copy.threshold), countLearn(copy.countLearn)
{
    _data = new InputData[13];
    weight = new InputData[13];
    std::memcpy(_data, copy._data, sizeof(InputData[13]));
    std::memcpy(weight, copy.weight, sizeof(InputData[13]));
}

Neuron::Neuron(Neuron&& move) : style(move.style), _data(move._data), weight(move.weight), threshold(move.threshold), countLearn(move.countLearn)
{
    move._data = nullptr;
    move.weight = nullptr;
    move.countLearn = 0;
    move.style.clear();
    move.threshold = 0.f;
}

Neuron& Neuron::operator=(const Neuron& copy)
{
    std::memcpy(_data, copy._data, sizeof(InputData[13]));
    std::memcpy(weight, copy.weight, sizeof(InputData[13]));
    style = copy.style;
    threshold = copy.threshold;
    countLearn = copy.countLearn;
    return *this;
}

Neuron& Neuron::operator=(Neuron&& move)
{
    delete[] _data;
    delete[] weight;
    _data = move._data;
    weight = move.weight;
    countLearn = move.countLearn;
    style = move.style;
    threshold = move.threshold;
    move._data = nullptr;
    move.weight = nullptr;
    move.countLearn = 0;
    move.style.clear();
    move.threshold = 0.f;
    return *this;
}

void Neuron::loadData(ifstream& in)
{
    in.read(reinterpret_cast<char*>(_data), sizeof(InputData[13]));
    in.read(reinterpret_cast<char*>(weight), sizeof(InputData[13]));
    in.read(reinterpret_cast<char*>(&countLearn), sizeof(countLearn));
}

void Neuron::saveData(ofstream& out)
{
    uint32_t len = style.length();
    out.write(reinterpret_cast<char*>(&len), sizeof(len));
    out.write(style.c_str(), len);
    out.write(reinterpret_cast<char*>(_data), sizeof(InputData[13]));
    out.write(reinterpret_cast<char*>(weight), sizeof(InputData[13]));
    out.write(reinterpret_cast<char*>(&countLearn), sizeof(countLearn));
}

void Neuron::setupData(MapMono& map)
{
    if(countLearn == 0)
    {
        for(int i = 0; i < 13; ++i)
        {
            _data[i].mean = map["lowlevel.mfcc.mean"][i];
            _data[i].max = map["lowlevel.mfcc.max"][i];
            _data[i].median = map["lowlevel.mfcc.median"][i];
            _data[i].min = map["lowlevel.mfcc.min"][i];
            _data[i].var = map["lowlevel.mfcc.var"][i];
        }
    } else {
        for(int i = 0; i < 13; ++i)
        {
            _data[i].mean = _data[i].mean / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.mean"][i] / (countLearn + 1.l);
            _data[i].max = _data[i].max / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.max"][i] / (countLearn + 1.l);
            _data[i].median = _data[i].median / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.median"][i] / (countLearn + 1.l);
            _data[i].min = _data[i].min / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.min"][i] / (countLearn + 1.l);
            _data[i].var = _data[i].var / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.var"][i] / (countLearn + 1.l);
        }
    }
    ++countLearn;
}

void Neuron::print(void){
    for(int i = 0; i < 13; i++){
        cout << _data[i].max
             << " " << _data[i].mean
             << " " << _data[i].median
             << " " << _data[i].min
             << " " << _data[i].var           
             << endl;
    }
}

const string& Neuron::getStyleName() const
{
    return style;
}

uint32_t Neuron::getCountLearning() const
{
    return countLearn;
}

Neuron::~Neuron()
{
    delete[] _data;
    delete[] weight;
}
