#include <stdio.h>
#include <math.h>

// This will be used to pass functions like sampleFunc as arguments to the bisect function.
// accepts float and returns float
typedef float(*FunctionPointer)(float); 


//this is an example function that will be passed to the bisect function
float sampleFunc(float x){
    return  3*x - 2 + cos(x);
}

//given that f(a) and f(b) give different signs and f(x) is continuous on [a,b]
//we can find the roots of the function by the bisection method
float bisect(FunctionPointer func,float a,float b){
    float mid;  // a variable to hold the middle of a and b

    // precision level is 0.0001 at this distance between b and a 
    // the value we find is precise enough so we stop the while loop
    while ((b-a) >= 0.0001) 
    {
        mid = (a+b)/2; //finding the mid value

        if (func(mid) == 0.0f) //if what we find is an actual root 
        {
            break;//just return early
        }
        //if the product of func(mid) and func(a) is negative
        //that means there is a sign change betweem mid and a
        //so the new interval becomes [mid,a] meaning b's value is replaced by mid
        //in more formal terms b = mid
        else if(func(mid) * func(a) < 0){ 
            b = mid;
        } else {
            a = mid;
        }
        
    }
    
    return mid;

}

int main(int argc, char const *argv[])
{
    float root = bisect(sampleFunc, 0.0f , 2.0f);
    // The expected output for the root of x^2 - 2 is approximately 1.4142 (sqrt(2)).
    // time complexity is O(log(b-a)/precision level) , precision level is 0.0001 in this case
    printf("root is %f\n ", root);
    return 0;
}
