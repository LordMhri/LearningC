/*
    This network determines whether or not a binary number has an even
    or odd number of 1's.

    It will have 3 input neurons -> this is a 3 bit parity checker, one for each bit
    1 hidden layer(2 neurons) -> for the classification
    1 output neuron -> even/odd classification

 */
#ifndef NEURAL_H
#define NEURAL_H

typedef struct Network 
{
    //number of neurons for each layer
    int n_hidden;
    int n_input;
    int n_output;
    
    //biases and weights of hidden and output layer
    double* hiddenBias;
    double* outputBias;
    double* hiddenWeight;
    double* outputWeight;

    //neuron array for hidden and output layer
    double* hiddenNeuron;
    double* outputNeuron;
} Network;

Network* initializeNetwork(Network *Network,int n_hidden,int n_output,int n_input);
double *predict(Network *network,double* inputs);
void train(Network *network,double *expectedOutput,double *inputs,double learningRate );


#endif