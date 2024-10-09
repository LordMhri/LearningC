/*
    This network determines whether or not a binary number has an even
    or odd number of 1's.

    It will have 3 input neurons -> this is a 3 bit parity checker, one for each bit
    1 hidden layer(2 neurons) -> for the classification
    1 output neuron -> even/odd classification

 */
#include <stdio.h>

#ifndef NEURAL_H
#define NEURAL_H


//this is the definition of the Network
typedef struct {

    size_t inputNeuronsCount; // number of neurons in the inputlayer -> 3 for the parity checker
    size_t hiddenNeuronsCount;// number of neurons in the hidden layer -> 2 because this is a very simple network,could be more though
    size_t outputNeuronsCount;// number of neurons in the output layer -> 1 for either odd/even


    //The weights and biases needed for the back propagation.
    
    double *outputWeight;
    double *hiddenWeight;
    double *outputBias;
    double *hiddenBias;
} Network; 


Network createNetwork(size_t inputNeuronsCount, size_t hiddenNeuronsCount,size_t outputNeuronsCount);//creates the network
void Train(Network *network,double *inputs,double *expectedOutput,double learningRate); //trains the network
double* Predict( Network *network,double* inputs); //returns the predicted value
void freeNetwork(Network *network); // free memory after training

#endif