#include "neuron.hpp"
#include <cmath>

Neuron::Neuron(const string &style)
    : style(style)
{
    _data = new InputData[13];
    countLearn = 0;
}

Neuron::Neuron(const Neuron &copy)
    : style(copy.style), countLearn(copy.countLearn)
{
    _data = new InputData[13];
    std::memcpy(_data, copy._data, sizeof(InputData[13]));
}

Neuron::Neuron(Neuron &&move) noexcept
    : style(move.style), _data(move._data), countLearn(move.countLearn)
{
    move._data = nullptr;
    move.countLearn = 0;
    move.style.clear();
}

Neuron &Neuron::operator=(const Neuron &copy)
{
    std::memcpy(_data, copy._data, sizeof(InputData[13]));
    style = copy.style;
    countLearn = copy.countLearn;
    return *this;
}

Neuron &Neuron::operator=(Neuron &&move) noexcept
{
    delete[] _data;
    _data = move._data;
    countLearn = move.countLearn;
    style = move.style;
    move._data = nullptr;
    move.countLearn = 0;
    move.style.clear();
    return *this;
}

void Neuron::loadData(ifstream &in)
{
    in.read(reinterpret_cast<char *>(_data), sizeof(InputData[13]));
    in.read(reinterpret_cast<char *>(&countLearn), sizeof(countLearn));
}

void Neuron::saveData(ofstream &out)
{
    uint32_t len = style.length();
    out.write(reinterpret_cast<char *>(&len), sizeof(len));
    out.write(style.c_str(), len);
    out.write(reinterpret_cast<char *>(_data), sizeof(InputData[13]));
    out.write(reinterpret_cast<char *>(&countLearn), sizeof(countLearn));
}

void Neuron::setupData(MapMono &map)
{
    if (countLearn == 0) {
        for (int i = 0; i < 13; ++i) {
            _data[i].mean = map["lowlevel.mfcc.mean"][i];
            _data[i].max = map["lowlevel.mfcc.max"][i];
            _data[i].median = map["lowlevel.mfcc.median"][i];
            _data[i].min = map["lowlevel.mfcc.min"][i];
            _data[i].var = map["lowlevel.mfcc.var"][i];
        }
    }
    else {
        for (int i = 0; i < 13; ++i) {
            _data[i].mean =
                _data[i].mean / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.mean"][i] / (countLearn + 1.l);
            _data[i].max = _data[i].max / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.max"][i] / (countLearn + 1.l);
            _data[i].median =
                _data[i].median / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.median"][i] / (countLearn + 1.l);
            _data[i].min = _data[i].min / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.min"][i] / (countLearn + 1.l);
            _data[i].var = _data[i].var / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.var"][i] / (countLearn + 1.l);
        }
    }
    ++countLearn;
}

MapMono Neuron::getNeuronDiff(MapMono &map)
{
    MapMono m(map);
    for (int i = 0; i < 13; i++) {
        m["lowlevel.mfcc.mean"][i] = fabs(_data[i].mean - map["lowlevel.mfcc.mean"][i]);
        m["lowlevel.mfcc.max"][i] = fabs(_data[i].max - map["lowlevel.mfcc.max"][i]);
        m["lowlevel.mfcc.median"][i] = fabs(_data[i].median - map["lowlevel.mfcc.median"][i]);
        m["lowlevel.mfcc.min"][i] = fabs(_data[i].min - map["lowlevel.mfcc.min"][i]);
        m["lowlevel.mfcc.var"][i] = fabs(_data[i].mean - map["lowlevel.mfcc.var"][i]);
    }
    return m;
}

void Neuron::print(void)
{
    for (int i = 0; i < 13; i++) {
        cout << _data[i].max
             << " " << _data[i].mean
             << " " << _data[i].median
             << " " << _data[i].min
             << " " << _data[i].var
             << endl;
    }
}

Neuron::~Neuron() noexcept
{
    delete[] _data;
}
