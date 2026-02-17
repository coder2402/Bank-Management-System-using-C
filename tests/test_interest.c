#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../interest.h"

// Robust float comparison
int is_near(float a, float b) {
    float epsilon = 0.0001f;
    float diff = fabs(a - b);
    a = fabs(a);
    b = fabs(b);
    float largest = (b > a) ? b : a;

    if (diff <= largest * epsilon)
        return 1;
    // Handle cases near zero
    if (diff <= epsilon)
        return 1;
    return 0;
}

void test_interest_boundary_values() {
    printf("Running test_interest_boundary_values...\n");

    // Case 1: Time is zero
    printf("  Testing t=0...\n");
    assert(is_near(interest(0.0f, 1000.0f, 5), 0.0f));

    // Case 2: Amount is zero
    printf("  Testing amount=0...\n");
    assert(is_near(interest(1.0f, 0.0f, 5), 0.0f));

    // Case 3: Rate is zero
    printf("  Testing rate=0...\n");
    assert(is_near(interest(1.0f, 1000.0f, 0), 0.0f));

    // Case 4: Smallest positive values (boundary near zero)
    printf("  Testing small values...\n");
    assert(is_near(interest(1.0f/365.0f, 1.0f, 1), 1.0f/36500.0f));

    // Case 5: Large values
    printf("  Testing large values...\n");
    assert(is_near(interest(100.0f, 1000000.0f, 20), 20000000.0f));

    // Case 6: Typical values
    printf("  Testing typical values...\n");
    assert(is_near(interest(2.0f, 5000.0f, 10), 1000.0f));

    printf("test_interest_boundary_values passed!\n");
}

int main() {
    test_interest_boundary_values();
    printf("All interest tests passed successfully!\n");
    return 0;
}
