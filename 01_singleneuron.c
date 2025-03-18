#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// y=x*3 model
// float data[][2] = {
//     {0, 0},
//     {1, 3},
//     {2, 6},
//     {3, 9},
//     {4, 12},
// };
// y=x*1.5 learn model
float data[][2] = {
    {0, 0},
    {1, 1.5f},
    {2, 3},
    {3, 4.5f},
    {4, 6},
};

#define data_count (sizeof(data)/sizeof(data[0]));

// Cost function based on derivitive for a linear regression model 
float cost(float weight) {
    float result = 0.0f;
    size_t n = data_count;
   
    for (size_t i = 0; i < n; ++i) {
        float x = data[i][0];
        float y = data[i][1];
        result += 2 * (x * weight - y) * x;
    }
    
    result /= n;
    return result;
}

float randf() {
    return (float) rand() / (float) RAND_MAX;
}

int main() {
    srand(time(0));
    
    float weight = randf() * 10.0f;
    float learn_rate = 0.1f;
    
    printf("initial cost = %f; initial weight = %f\n", cost(weight), weight);

    for (size_t i = 0; i < 12; ++i) {
        // derivitive (velocity) of weight
        float dw = cost(weight);

        weight -= learn_rate * dw;
        printf("cost = %f; weight = %f\n", cost(weight), weight);
    }

    printf("\nfinal weight = %f\n", weight);
    return 0;
}