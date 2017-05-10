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
    uint32_t countLearn;
public:
    Neuron(const string &style);
    Neuron(const Neuron &copy);
    Neuron(Neuron&& move) noexcept;
    Neuron& operator=(const Neuron &copy);
    Neuron& operator=(Neuron&& move) noexcept;
    void loadData(ifstream&);
    void saveData(ofstream&);
    void setupData(MapMono &map);
    MapMono getNeuronDiff(MapMono &map);
    void print(void);

    const string& getStyleName() const
    {
        return style;
    }

    uint32_t getCountLearning() const
    {
        return countLearn;
    }

    ~Neuron() noexcept;
};
