#pragma once
#include "essentaisAlgoritms.hpp"
#include "common.hpp"
using namespace std;

typedef struct {
    double max;
    double mean;
    double median;
    double min;
    double var;
} InputData;

class Neuron
{
private:
    string style;
    InputData *_data;
    InputData *weight;
    double power;
    double threshold;
    uint32_t countLearn;
public:
    Neuron(const string& style);
    Neuron(const Neuron& copy);
    Neuron(Neuron&& move);
    Neuron& operator=(const Neuron& copy);
    Neuron& operator=(Neuron&& move);
    void loadData(ifstream&);
    void saveData(ofstream&);
    void setupData(MapMono& map);
    void print(void);
    const string& getStyleName() const;
    uint32_t getCountLearning() const;
    ~Neuron();
};
