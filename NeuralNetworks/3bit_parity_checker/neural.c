#include "neural.h"
#include <stdlib.h>
#include <math.h>

double randf(){
    return  (double) rand() / RAND_MAX;
}

//activation function to introduce non-linearity
//gives value between 0 and 1
double sigmoid(double x) {
    return (1.0)/(1.0 + exp(-x));
}
double sigmoid_prime(double x){
    return x * (1.0-x);
}

Network *initializeNetwork(Network *network,int n_input,int n_hidden,int n_output) {
    //initialize values
    network->n_input = n_input;
    network->n_hidden = n_hidden;
    network->n_output = n_output;


    //allocate space
    network->hiddenBias = calloc(n_hidden,sizeof(*network->hiddenBias));
    network->outputBias = calloc(n_output,sizeof(*network->outputBias));
    network->hiddenWeight = calloc(n_hidden*n_input,sizeof(*network->hiddenWeight));
    network->outputWeight = calloc(n_hidden*n_output,sizeof(*network->outputWeight));
    network->hiddenNeuron = calloc(n_hidden,sizeof(network->hiddenNeuron));
    network->outputNeuron = calloc(n_output,sizeof(network->outputNeuron));

    //intialize weights
    for (int i = 0; i < n_hidden; i++)
    {
        network->hiddenWeight[i] = randf();
    }
    for (int i = 0; i < n_output; i++)
    {
        network->outputWeight[i] = randf();
    }
    

    return network;
}

double *predict(Network *network,double* inputs){


    //forward propagation to the hidden layer from the input layer
    for (int i = 0; i < network->n_hidden; i++)
    {
        double weightedSum = network->hiddenWeight[i]; 
        for (int j = 0; j < network->n_input; j++)
        {
            weightedSum += inputs[j] * network->hiddenWeight[j * network->n_hidden + i];
        }
        network->hiddenNeuron[i] = sigmoid(weightedSum + network->hiddenBias[i]);
    }

    //forward propagation to the output layer from the hidden layer
    for (int i = 0; i < network->n_output; i++)
    {
        double weightedSum = 0;
        for (int j = 0; j < network->n_hidden; j++) {
            weightedSum += network->hiddenNeuron[j] * network->outputWeight[j * network->n_output + i];
        }
        network->outputNeuron[i] = sigmoid(weightedSum + network->outputBias[i]);
    }

    return network->outputNeuron;
}

// Training the network using backpropagation
void train(Network *network, double *expectedOutput, double *inputs, double learningRate) {
    // Get the network's prediction for the given inputs
    double *predictedOutput = predict(network, inputs);

    // Calculate the output errors for each output neuron
    double outputError[network->n_output];
    for (int i = 0; i < network->n_output; i++) {
        outputError[i] = predictedOutput[i] - expectedOutput[i];
    }

    // Calculate the gradients for each output neuron
    double outputGradient[network->n_output];
    for (int i = 0; i < network->n_output; i++) {
        outputGradient[i] = outputError[i] * sigmoid_prime(network->outputNeuron[i]);
    }

    // Calculate the hidden layer gradients
    double hiddenGradient[network->n_hidden];
    for (int i = 0; i < network->n_hidden; i++) {
        hiddenGradient[i] = 0;
        for (int j = 0; j < network->n_output; j++) {
            hiddenGradient[i] += outputGradient[j] * network->outputWeight[i * network->n_output + j];
        }
        hiddenGradient[i] *= sigmoid_prime(network->hiddenNeuron[i]);
    }

    // Update the weights between hidden and output neurons
    for (int i = 0; i < network->n_output; i++) {
        for (int j = 0; j < network->n_hidden; j++) {
            network->outputWeight[j * network->n_output + i] -= learningRate * outputGradient[i] * network->hiddenNeuron[j];
        }
        network->outputBias[i] -= learningRate * outputGradient[i];
    }

    // Update the weights between input and hidden neurons
    for (int i = 0; i < network->n_hidden; i++) {
        for (int j = 0; j < network->n_input; j++) {
            network->hiddenWeight[j * network->n_hidden + i] -= learningRate * hiddenGradient[i] * inputs[j];
        }
        network->hiddenBias[i] -= learningRate * hiddenGradient[i];
    }
}
