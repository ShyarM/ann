# include "ann.hpp"
# include <iostream>
# include <cmath>


using namespace::std;


long double heaviside(long double value) {
    
 
    if(value>=0) { return 1;}
    
    return 0;
}

long double sigmoid(long double value) {
    
 
    return (1/(1+exp(-value)));
    
}

long double zero(long double value) { return 0;}

int main() {
 
    Neuron n;
    n.set(3,sigmoid);
    n.setInput((long double)(5),(long double)(23),(long double)(34));
    cout<<"Net output: "<<n.netOutput()<<endl;
    cout<<"Output: "<<n.Output()<<endl;
    return 0;
}
