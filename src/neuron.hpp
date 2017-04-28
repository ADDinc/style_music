#ifndef NEURON_HPP
#define NEURON_HPP

//#pragma once
#include "essentaisAlgoritms.hpp"
#include "common.hpp"
using namespace std;

#include <iostream>
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
    void loadData(ifstream&);
    void saveData(ofstream&);
    void setupData(MapMono map);
    void print(void);
    const string& getStyleName() const;
    ~Neuron();
};

#endif //NEURON_HPP
