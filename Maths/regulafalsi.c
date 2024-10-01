#include <stdio.h>
#include <math.h>

typedef float(*FunctionPointer) (float);

float sampleFunc(float x){
    return  3*x - 2 + cos(x);
}

float regulaFalsi(FunctionPointer func,float x0,float x1){
    float x2 = x1 - ( func(x1) * (x0-x1)/(func(x0) - func(x1)));

    while (fabs(func(x2)) >0.0001)
    {
        

       if (func(x2) * func(x0) < 0) //func(x2) and func(x0) are opposite signs
       {
        x1 = x2; // Root lies between x0 and x2, update x1
       } else{
        x0 =x2; // Root lies between x1 and x2,update x0
       }

       x2 = x1 - ( func(x1) * (x0-x1)/(func(x0) - func(x1))); //update x2 with the new updated values

    //under this difference, there is no change between x1 and x2 so we return x2
       if (fabs(x1-x2) < 0.00001) 
       {
        break;
       }
       
    }

    return x2;
    
}

int main(int argc, char const *argv[])
{
    float root = regulaFalsi(sampleFunc,0.0f,2.0f);
    printf("root is %f\n" , root);
    return 0;
}
