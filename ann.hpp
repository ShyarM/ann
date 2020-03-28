# ifndef __ANN__H__
# define __ANN__H__

# include <stdexcept>
# include <cstdarg>
# include <iostream>
# include <vector>
# include <ctime>
# include <cassert>
# include <limits>
# include <cmath>

class err_invalid_arg{};

static const char* err_msg_out_of_range = "ERROR: OUT OF RANGE. ";

long double Heaviside(long double value); 

long double Bipolar(long double value); 
 
long double Sigmoid(long double value);

long double Random(long double min,long double max);

class Neuron {
    
public:
    Neuron();
    ~Neuron();
    Neuron (int nweights,long double (*func)(long double),long double bias = 0);
    void set(int nweights,long double (*func)(long double),long double bias = 0);
    void setInput(...);
    void setInput(std::vector<long double>& input);
    void setWeight(int index,long double value);
    long double getWeight(int index);
    void setTargetOutput(long double value);
    void setBias(long double value);
    long double getBias() const ;
    long double netOutput();
    long double Output();
    int getNumbWeights() const;
    void setInput(int index,long double value);
    long double getTargetOutput() const;
    void setAllWeights(long double weight);
    void setAllWeights(long double min,long double max);
    void displayAllWeights();
    void setShift(long double value);
    long double getShift() const;
    
protected:
    long double (*act_func)(long double );
    long double* mWeights;
    int nWeights;
    bool isSet;
    long double mTargetOutput;
    long double mBias;
    long double* mInputs;
    bool isInputSet;
    long double mShift;
};

class Layer {
    
public:
    Layer(int nneurons,long double (*func)(long double));
    void set(int nneurons,long double (*func)(long double));
    Layer();
    ~Layer();
    void setNeuron(int neuron_index, int nweights,long double bias = 0);
    void setNeuronWeight(int neuron_index,int weight_index,long double value);
    long double getNeuronWeight(int neuron_index,long double value);
    void setNeuronDesiredOutput(int neuron_index,long double value);
    void setNeuronInput(int neuron_index,...);
    void setNeuronInput(int neuron_index,std::vector<long double>& inputs);
    void setInput(std::vector<std::vector<long double>>& inputs);
    long double Output(int neuron_index);
    void setAllNeurons(int nweights);

protected:
    int nNeurons;
    Neuron* mNeurons;
    bool isSet;
    long double (*act_func)(long double);

};


class Ann {
    
public:
    Ann(int ninputs,int noutputs,int nhidden,long double (*func)(long double));
    void set(int niputs,int noutputs,int nhidden,long double (*func)(long double));
    
    ~Ann();
    
    void setInputs(std::vector<long double>& inputs);
 
protected:
    int nInputs;
    int nOutputs;
    long double* mInputs;
    int nHiddenLayers;
    int nNeuronsHidden;
    Layer* mHiddenLayers;
//     Layer  mInputLayer;
    Layer  mOutputLayer;
    long double (*act_func)(long double value);
    bool isInputSet;
    
};



# endif 
    
