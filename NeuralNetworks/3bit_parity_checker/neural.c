#include "neural.h"
#include <stdlib.h>
#include <math.h>


double randf(){
    return (double)rand()/ RAND_MAX; //generates a random number between 0 and 1
    //rand generates a number between 0 and 2^(31)-1
    //RAND_MAX is 2^(31) - 1
}


Network createNetwork(size_t inputCount,size_t hiddenCount,size_t outputCount){
    Network network;
    network.inputNeuronsCount = inputCount;
    network.outputNeuronsCount = outputCount;
    network.hiddenNeuronsCount = hiddenCount;

    //allocate memory for weights and biases
    network.hiddenWeight = malloc(inputCount * hiddenCount * sizeof(double));
    network.hiddenBias = malloc(hiddenCount * sizeof(double));
    network.outputWeight = malloc(hiddenCount * outputCount * sizeof(double));
    network.outputBias = malloc(outputCount * sizeof(double));

    //initialize weights and biases randomly
    for (size_t i = 0; i < inputCount*hiddenCount; i++)
    {
        network.hiddenWeight[i] = randf();
    }
    for (size_t i = 0; i < hiddenCount; i++)
    {
        network.hiddenBias[i] = randf();
    }
    for (size_t i = 0; i < outputCount*hiddenCount; i++)
    {
        network.outputWeight[i] = randf();
    }
    for (size_t i = 0; i < outputCount; i++)
    {
        network.outputBias[i] = randf();
    }

    return network;
}

void freeNetwork(Network *network) {
    free(network->hiddenWeight);
    free(network->hiddenBias);
    free(network->outputWeight);
    free(network->outputBias);
}

/*sigmoid function used to introduce non-linearity
gives a value between 0 and 1
appraoches 0 for big negative values
appraoches 1 for big positive values
approaches 0 as we approach 0 */
double sigmoid(double x) {
    return 1.0/(1.0 + exp(-x));
}


double* Predict(Network *network,double *inputs){
    double *hidden = malloc((network->hiddenNeuronsCount) * sizeof(double));//assuming two hidden neurons in the hidden layer

    //forward propagation through the hidden layer
    for (size_t i = 0; i < network->hiddenNeuronsCount; i++)
    {
        //initialize hidden neuron with it's bias
        // hiddenNeuronActivation = bias[i]
        hidden[i] = network->hiddenBias[i];
        for (size_t j = 0; j < network->inputNeuronsCount; j++)
        {
            //accumulate weighted input to hidden neuron
            //hiddenNeuronActivation = bias + summation of (each input neuron * its corresponding weight)
            //j*network->hiddenNeuronsCount + i is used to find the index of the weight from input neuron j to hidden neuron i
            hidden[i] += inputs[j]*network->hiddenWeight[j*network->hiddenNeuronsCount + i];
        }
        //applying the sigmoid function to approximate the value to between 0 and 1
        hidden[i] = sigmoid(hidden[i]);
    }

    //forward propagation through the output layer
    double *output = malloc(network->outputNeuronsCount * sizeof(double));//one output neuron yes or no
    for (size_t i = 0; i < network->outputNeuronsCount; i++)
    {
        output[i] = network->outputBias[i];
        for (size_t j = 0; j < network->hiddenNeuronsCount ; j++)
        {
        // Accumulate weighted input to output neuron
        // outputNeuronActivation = bias + summation of (each hidden neuron * its corresponding weight)
        //j*network->outputNeuronsCount + i is used to find corresponding weight from hidden neuron j to output neuron i
          output[i] += hidden[j] * network->outputWeight[j*network->outputNeuronsCount + i];
        }
        //sigmoid function to introduce non-linearity
        output[i] = sigmoid(output[i]);         
    }
    
    free(hidden);

    return output;
    
}


void Train(Network *network,double *inputs,double *expectedOutput,double learningRate) {


    //get the predicted output
    double *predictedOutput = Predict(network,inputs);

    //get the error from our prediction
    double outputError = predictedOutput[0] - expectedOutput[0];

    //find the gradient for the output neuron
    //derivative of the sigmoid function is f'(x)  = f(x) * (1-f(x))
    double outputGradient = outputError * predictedOutput[0] * (1 - predictedOutput[0]);

    //backpropagating the error to the hidden layer
    double hiddenGradient[network->hiddenNeuronsCount];


    double *hiddenActivations = malloc(network->hiddenNeuronsCount * sizeof(double));//allocate memory for hiddenNeurons
    for (size_t i = 0; i < network->hiddenNeuronsCount; i++)
    {  
        //get the contribution of each hidden neuron to the outputGradient
        hiddenGradient[i] = outputGradient * network->outputWeight[i] * hiddenActivations[i] * (1-hiddenActivations[i]);

    }

    //update weight in the output layer
    for (size_t i = 0; i < network->hiddenNeuronsCount; i++)
    {
        network->outputWeight[i] -= learningRate * outputGradient * hiddenActivations[i];
    }
    

   //update bias in the output layer
   network->outputBias[0] -= learningRate * outputGradient;  

    //update weights and biases in the hiddenlayer
   for (size_t i = 0; i < network->inputNeuronsCount; i++)
   {
    for (size_t j = 0; j < network->hiddenNeuronsCount; j++)
    {
        network->hiddenWeight[i * network->hiddenNeuronsCount +j] -= learningRate * hiddenGradient[j] * inputs[i];
    } 
   }

   //update hidden biases
   for (size_t i = 0; i < network->hiddenNeuronsCount; i++)
   {
        network->hiddenBias[i] -= learningRate * hiddenGradient[i];
   }
   

   free(hiddenActivations);
   free(predictedOutput);
}