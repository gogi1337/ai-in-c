#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 5

/**
 * Function to predict using a polynomial model
 * weights: Array of coefficients [w0, w1, w2, ...]
 * x: Input value
 * degree: Degree of the polynomial plus 1 (for constant term)
 */
float predict(float x, float weights[MAX_DEGREE], int degree) {
    float result = weights[0];  // Constant term
    for (size_t j = 1; j < degree; j++) {
        result += weights[j] * pow(x, j);
    }
    return result;
}

/**
 * Trains and validates a power function model (x^n)
 * power: The power to model (2 = x^2, 3 = x^3, etc.)
 */
void model_power_function(int power) {
    const int num_samples = 6;
    float data[10][2];  // Up to 10 data points
    
    printf("\n=======================================\n");
    printf("MODELING FUNCTION: f(x) = x^%d\n", power);
    printf("=======================================\n");
    
    for (size_t i = 0; i < num_samples; i++) {
        data[i][0] = (float)i;         // x value
        data[i][1] = pow(i, power);    // y = x^power
    }
    
    int degree = power + 1;
    
    float weights[MAX_DEGREE] = {0};
    weights[power] = 1.0f;
    
    printf("\nModel validation for x^%d:\n", power);
    printf("---------------------------------------------\n");
    printf("x\t| y=x^%d\t\t| Predicted\t| Error\n", power);
    printf("---------------------------------------------\n");
    
    // On training data
    for (size_t i = 0; i < num_samples; i++) {
        float x = data[i][0];
        float actual = data[i][1];
        float predicted = predict(x, weights, degree);
        printf("%.1f\t| %-10.1f\t| %-10.6f\t| %-10.9f\n", 
               x, actual, predicted, fabs(actual - predicted));
    }
    
    float test_x[] = {1.5, 2.5, 3.5, 5.0};
    printf("\nTest on new data:\n");
    printf("---------------------------------------------\n");
    printf("x\t| y=x^%d\t\t| Predicted\t| Error\n", power);
    printf("---------------------------------------------\n");
    
    for (size_t i = 0; i < sizeof(test_x) / sizeof(test_x[0]); i++) {
        float x = test_x[i];
        float actual = pow(x, power);
        float predicted = predict(x, weights, degree);
        printf("%.1f\t| %-10.2f\t| %-10.6f\t| %-10.9f\n", x, actual, predicted, fabs(actual - predicted));
    }

    printf("\nFunction: f(x) = ");
    int printed_term = 0;
    
    for (size_t i = 0; i < degree; i++) {
        if (weights[i] != 0) {
            if (printed_term > 0) {
                printf(" + ");
            }
            
            if (i == 0) {
                printf("%.1f", weights[i]);
            } else if (i == 1) {
                printf("%.1f*x", weights[i]);
            } else {
                printf("%.1f*x^%d", weights[i], i);
            }
            
            printed_term++;
        }
    }
    printf("\n\n");
}

int main() {
    int powers[] = {2, 3, 4};
    
    for (size_t i = 0; i < 3; i++) {
        model_power_function(powers[i]);
    }
    
    printf("=======================================\n");
    printf("MIXED TESTING EXAMPLES\n");
    printf("=======================================\n");
    
    // float test_values[] = {2.5, 4.2, 6.0};
    float test_values[] = {2.1, 4.9, 4.1, 5.9};
    
    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        float x = test_values[i];
        printf("For x = %.1f:\n", x);
        
        for (int power = 2; power <= 4; power++) {
            float weights[MAX_DEGREE] = {0};
            weights[power] = 1.0f;    
            float actual = pow(x, power);
            float predicted = predict(x, weights, power+1);
            
            printf("  x^%d = %-10.6f (Actual: %-10.6f, Error: %-10.9f)\n", power, predicted, actual, fabs(actual - predicted));
        }
        printf("\n");
    }
    
    return 0;
}
