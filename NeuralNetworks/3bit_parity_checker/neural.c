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
        for (int j = 0; j < network->n_hidden; j++)
        {
            weightedSum += inputs[j] * network->outputWeight[j * network->n_output + i];
        }
        network->outputNeuron[i] = sigmoid(weightedSum + network->outputBias[i]);
        
    }
    
    return network->outputNeuron;
    
}

void train(Network *network,double *expectedOutput,double *inputs,double learningRate ) {

    //this gives me only one value
        double *predictedOutput = predict(network,inputs);

        //this only works because we have a single output neuron
        double error = predictedOutput[0] - expectedOutput[0];
        //gradient is f'(x) * (1-f(x))
        //this also is only valid becuse outputNeuron is 1
        double gradient = error * sigmoid_prime(network->outputNeuron[0]);

        double hiddenGradient[network->n_hidden];
        //find gradient for each hidden neuron
        for ( int i = 0; i < network->n_hidden; i++)
        {
            hiddenGradient[i] = (gradient * network->outputWeight[i]) * sigmoid_prime(network->hiddenNeuron[i]);
        }

        //update weight in the hidden layer
        for (int i = 0; i < network->n_hidden; i++)
        {
            network->hiddenWeight[i] -= learningRate * gradient * network->hiddenNeuron[i];
        }
        
        network->outputBias[0] -= learningRate * gradient;  

        // Update weights and biases in the hidden layer
        for (size_t i = 0; i < network->n_hidden; i++) {
            for (size_t j = 0; j < network->n_input; j++) {
                // Update weight connecting input j to hidden neuron i
                network->hiddenWeight[i * network->n_input + j] -= learningRate * hiddenGradient[i] * inputs[j];
            }
        }

        // Update biases in the hidden layer
        for (size_t i = 0; i < network->n_hidden; i++) {
            network->hiddenBias[i] -= learningRate * hiddenGradient[i];
        }
            

}