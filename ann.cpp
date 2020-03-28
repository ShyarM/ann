# include "ann.hpp"


//**************ACTIVATION FUNCTIONS********//

long double Heaviside(long double value) {
    
 
    return (value>=0 ? 1 : 0);
    
}

long double Bipolar(long double value) {
    
return (value>=0 ? 1 : -1);
}

long double ldouble_inf = std::numeric_limits<long double>::infinity();

long double Sigmoid(long double value) {
    
    long double exp = expl(-1*value);
    if(exp!=ldouble_inf) {
    return ((1-exp)/(1+exp));
    }
    
    return -1;
}

//////////////////////////////////////////////////////
long double Random(long double min,long double max) {
    assert(max>=min);
 static bool is_first = true;
 
 if(is_first) {
    
  std::srand(std::time(NULL));
is_first = false;  
 }


 return (min + (max-min)*(Sigmoid((long double)((long double)std::rand()/(long double)std::rand()))));
 
}


///************************************///
///***********NEURON CLASS*************///
///************************************///
Neuron::Neuron(int nweights,long double (*func)(long double),long double bias){
  
    set(nweights,func,bias);
    
}
void Neuron::set(int nweights,long double (*func)(long double),long double bias){
    
 nWeights = nweights;   
 act_func = func;   
 mWeights  =  new long double[nWeights];
 isSet = true;
 mBias = bias;
 isInputSet = false;
 mInputs = new long double[nWeights];

 for(int i=0;i<nWeights;i++) {
     
  mWeights[i] = Random(-1,1);  
 }
 
}

Neuron::Neuron() {
    
 isSet = false;   
 
}

Neuron::~Neuron() {
 if(isSet) {
  
     delete mWeights;
     if(isInputSet) {
         delete mInputs;
     }
 }
}

long double Neuron::netOutput() {
 
    if(isInputSet) {
        long double sum = -1*mBias;
        for(int i=0;i<nWeights;i++) {
            
            sum += mInputs[i]*mWeights[i];
        }
        
        return sum;
    }
    
    std::cout<<"All Inputs must be set! "<<std::endl;
}

long double Neuron::Output() {
    
 return act_func(this->netOutput());   
    
}

long double Neuron::getWeight(int index) {
    
 if(index<nWeights) {
    return mWeights[index];
 }
 
 throw std::out_of_range(err_msg_out_of_range);
}

void Neuron::setWeight(int index,long double value) {
 
    if(index<nWeights) {
    mWeights[index] = value;
 }
 else {
 throw std::out_of_range(err_msg_out_of_range);
}
}

void Neuron::setTargetOutput(long double value) {
    
   mTargetOutput  = value;
}

long double Neuron::getTargetOutput() const {
 
    return mTargetOutput;
    
}
void Neuron::setBias(long double value) {
    
    mBias = value;
    
}
long double Neuron::getBias() const {
 
    return mBias;
}

int Neuron::getNumbWeights() const {
 
    return nWeights;
}
void Neuron::setInput(...) {
    if(isSet) {
    va_list list;
    va_start(list,nWeights);
    isInputSet = true;
    for(int i=0;i<nWeights;i++) {
     
        mInputs[i] = va_arg(list,long double);
        
    }
    va_end(list);
    }
    
    else {
     
        throw std::out_of_range(err_msg_out_of_range);
        
    }
}
 void Neuron::setInput(int index,long double value) {
  
     mInputs[index] = value;
 }
 
 void Neuron::setInput(std::vector<long double>& input) {
if(input.size()==nWeights) {
    int i  = 0;
    for( long double element : input) {
     
        mInputs[i] = element;
        
        i++;
    }
    
    isInputSet = true;
}
else {
    
    throw std::out_of_range(err_msg_out_of_range);
}
     
 }
 
 
 void Neuron::setAllWeights(long double weight) {
     
     for(int i = 0;i<nWeights;i++) {
      
         mWeights[i] = weight;
         
     }
     
 }
 
 void Neuron::displayAllWeights() {
     
     for(int i=0;i<nWeights;i++) {
         
         std::cout<<i<<" : "<<mWeights[i]<<std::endl;
         
     }
     
 }

 
 void Neuron::setShift(long double value ) { mShift = value;}
 
 long double Neuron::getShift() const { return mShift;}
 
 void Neuron::setAllWeights(long double min,long double max) {
  
     for(int i =0;i<nWeights;i++) {
     
         setWeight(i,Random(min,max));
     }
 }
 
 //****************************************//
 //**************LAYER CLASS**************//
 //**************************************//
 
Layer::Layer(int nneurons,long double (*func)(long double)) {
 nNeurons = nneurons;   
 mNeurons = new Neuron[nneurons];
 isSet = true;
 act_func = func;
}

Layer::Layer() {
 
    isSet = false;
    
}

 void Layer::setNeuron(int neuron_index,int nweights,long double bias){
     
     if((isSet)&&(neuron_index<nNeurons)) {
         
         return mNeurons[neuron_index].set(nweights,act_func,bias);
     }
     
     
         
         throw std::out_of_range(err_msg_out_of_range);
 
 }
 

 void Layer::setNeuronWeight(int neuron_index,int weight_index,long double value) {
     
     if((isSet)&&(neuron_index<nNeurons)){
     return mNeurons[neuron_index].setWeight(weight_index,value);
     }
     
      
         throw std::out_of_range(err_msg_out_of_range);
     
 }  
 
 void Layer::setAllNeurons(int nweights) {
     
         if((isSet)){
     
             for(int i=0;i<nNeurons;i++) {
              setNeuron(i,nweights);   
                 
             }
     }
      
         throw std::out_of_range(err_msg_out_of_range);
     
 }  
 
 
 Layer::~Layer() {
  
     if(isSet) {
     
         delete[] mNeurons;
     }
 }
 

 void Layer::setNeuronInput(int neuron_index,...) {
  
     if((isSet)&&(neuron_index<nNeurons)) {
       
         va_list list;
         int nweights = mNeurons[neuron_index].getNumbWeights();
         va_start(list,nweights);
         for(int i=0;i<nweights;i++) {
          
             mNeurons[neuron_index].setInput(i,(long double)(va_arg(list,long double)));
         }
         va_end(list);
    
     } 
     else {
      
         throw std::out_of_range(err_msg_out_of_range);
     }
 }
 void Layer::setNeuronInput(int neuron_index,std::vector<long double>& inputs) {
  
     if(neuron_index<=nNeurons) {
     
        mNeurons[neuron_index].setInput(inputs);
     
     }
     
     else {
      
         throw std::out_of_range(err_msg_out_of_range);
     }
 }
 void Layer::setInput(std::vector<std::vector<long double>>& inputs) {
     
if(inputs.size()!=nNeurons) {
    
    for(int i = 0;i<nNeurons;i++) {
    
        setNeuronInput(i,inputs[i]);
    }
}

else {
    
    std::cout<<"All neurons must be set!"<<std::endl;
}
     
 }
long double Layer::Output(int neuron_index) {
 
    if(neuron_index<=nNeurons) {
        
       return  mNeurons[neuron_index].Output();
    }
    
    else {
     
        throw std::out_of_range(err_msg_out_of_range);
    }
}
void Layer::set(int nneurons,long double (*func)(long double)) {
    
    
    nNeurons = nneurons;
    mNeurons = new Neuron[nNeurons];
    isSet = true;
    act_func = func;
}
 //////*******************************//////
 /////********* Ann Class ************//////
 //////*******************************//////
 
 void Ann::set(int ninputs,int noutputs,int nhidden,long double (*func)(long double)) {
     nInputs = ninputs;
     nOutputs = noutputs;
     nHiddenLayers = nhidden;
     mHiddenLayers = new Layer[nHiddenLayers];
    nNeuronsHidden = ninputs;
    mInputs = new long double[nInputs];
    
//      mInputLayer.set(nInputs,act_func);
//     for(int i =0;i<nInputs;i++) {
//         
//     mInputLayer.setNeuron(i,1);   
//         
//     }
     mOutputLayer.set(nOutputs,act_func);
     for(int i =0;i<nOutputs;i++) {
         
         mOutputLayer.setNeuron(i,nNeuronsHidden);
     }
     act_func  = func;
     for(int i=0;i<nHiddenLayers;i++) {
         int n_neurons = (i==0 ? ninputs : nNeuronsHidden);
         mHiddenLayers[i] = Layer(n_neurons,act_func);
         
         for(int j =0;j<nNeuronsHidden;j++) {
          
             mHiddenLayers[i].setNeuron(j,nNeuronsHidden);
         }
     }
     
 }
 
 
 Ann::Ann(int ninputs,int noutputs,int nhidden,long double (*func)(long double)){
     
  
     set(ninputs,noutputs,nhidden,func);
     isInputSet = false;
 }
 
Ann::~Ann() {
    
    delete[] mHiddenLayers;
    delete mInputs;
}

void Ann::setInputs(std::vector<long double>& inputs) {
    
    if(inputs.size()==nInputs) {
        
      for(int i =0;i<nInputs;i++) {
          
       mInputs[i] = inputs[i];   
      }
      
      isInputSet = true;
    }
    
    else {
        
     throw std::out_of_range(err_msg_out_of_range);   
    }
}
