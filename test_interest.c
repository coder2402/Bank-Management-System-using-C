#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "interest.h"

#define EPSILON 0.001

int main() {
    float result;

    // Test Case 1: Standard calculation
    // 2 years, $1000, 5% rate -> (5 * 2 * 1000) / 100 = 100
    result = interest(2.0, 1000.0, 5);
    printf("Test Case 1: interest(2.0, 1000.0, 5) = %f, Expected = 100.000000\n", result);
    assert(fabs(result - 100.0) < EPSILON);

    // Test Case 2: Zero amount
    result = interest(1.0, 0.0, 5);
    printf("Test Case 2: interest(1.0, 0.0, 5) = %f, Expected = 0.000000\n", result);
    assert(fabs(result - 0.0) < EPSILON);

    // Test Case 3: Zero rate
    result = interest(1.0, 1000.0, 0);
    printf("Test Case 3: interest(1.0, 1000.0, 0) = %f, Expected = 0.000000\n", result);
    assert(fabs(result - 0.0) < EPSILON);

    // Test Case 4: Zero time
    result = interest(0.0, 1000.0, 5);
    printf("Test Case 4: interest(0.0, 1000.0, 5) = %f, Expected = 0.000000\n", result);
    assert(fabs(result - 0.0) < EPSILON);

    // Test Case 5: Decimal time (e.g., 6 months = 0.5 years)
    // 0.5 years, $1000, 10% rate -> (10 * 0.5 * 1000) / 100 = 50
    result = interest(0.5, 1000.0, 10);
    printf("Test Case 5: interest(0.5, 1000.0, 10) = %f, Expected = 50.000000\n", result);
    assert(fabs(result - 50.0) < EPSILON);

    // Test Case 6: Decimal amount
    // 1 year, $100.50, 10% rate -> (10 * 1 * 100.50) / 100 = 10.05
    result = interest(1.0, 100.50, 10);
    printf("Test Case 6: interest(1.0, 100.50, 10) = %f, Expected = 10.050000\n", result);
    assert(fabs(result - 10.05) < EPSILON);

    // Test Case 7: Large values
    // 10 years, $1,000,000, 5% rate -> (5 * 10 * 1,000,000) / 100 = 500,000
    result = interest(10.0, 1000000.0, 5);
    printf("Test Case 7: interest(10.0, 1000000.0, 5) = %f, Expected = 500000.000000\n", result);
    assert(fabs(result - 500000.0) < EPSILON);

    printf("\nAll tests passed successfully!\n");
    return 0;
}
