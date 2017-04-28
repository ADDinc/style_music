#include "neuron.hpp"

Neuron::Neuron(const string& style) : style(style)
{
    _data = new InputData[20];
    weight = new InputData[20];
    countLearn = 0;
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

void Neuron::setupData(MapMono map)
{
    if(this->countLearn == 0){
        for(int i = 0; i < 13; i++) {
            _data[i].mean = map["lowlevel.mfcc.mean"][i];
            _data[i].max = map["lowlevel.mfcc.max"][i];
            _data[i].median = map["lowlevel.mfcc.median"][i];
            _data[i].min = map["lowlevel.mfcc.min"][i];
            _data[i].var = map["lowlevel.mfcc.var"][i];
        }
        countLearn++;
    } else {
        for(int i = 0; i < 13; i++) {
            _data[i].mean = _data[i].mean / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.mean"][i] / (countLearn + 1.l);
            _data[i].max = _data[i].max / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.max"][i] / (countLearn + 1.l);
            _data[i].median = _data[i].median / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.median"][i] / (countLearn + 1.l);
            _data[i].min = _data[i].min / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.min"][i] / (countLearn + 1.l);
            _data[i].var = _data[i].var / (1.l + 1.l / countLearn) + map["lowlevel.mfcc.var"][i] / (countLearn + 1.l);
        }
        countLearn++;
    }
}

void Neuron::print(void){
    for(int i = 0; i < 13; i++){
        cout << _data[i].mean
             << " " << _data[i].max
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

Neuron::~Neuron()
{
    delete[] _data;
    delete[] weight;
}
