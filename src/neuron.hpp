#ifndef NEURON_HPP
#define NEURON_HPP

//#pragma once
#include "common.hpp"
using namespace std;

typedef struct {
    double max;
    double mean;
    double min;
    double var;
} InputData;

class Neuron
{
private:
    string style;
    InputData *_data;
    double  weight[][4];
    double power;
    double threshold;
    uint32_t countLearn;
public:
    Neuron(const string& style);
    void loadData();
    void saveData();
    const string& getStyleName() const;
    ~Neuron();
};

#endif //NEURON_HPP
