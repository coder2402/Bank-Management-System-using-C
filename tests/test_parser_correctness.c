#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

// Optimized parsing logic as implemented in Bank_Management_system.c
int parse_name_manual(const char *line, char *read_name) {
    char *ptr_start = strchr(line, ' ');
    if (ptr_start) {
        // Robustly skip all whitespace between account number and name
        while (*ptr_start == ' ') ptr_start++;

        if (*ptr_start != '\0') {
            char *ptr_end = strchr(ptr_start, ' ');
            if (ptr_end) {
                size_t len = ptr_end - ptr_start;
                if (len < 60) {
                    memcpy(read_name, ptr_start, len);
                    read_name[len] = '\0';
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    printf("Running parser correctness tests...\n");

    char buffer[60];

    // Test case 1: Standard valid record (single space)
    char *line1 = "1001 TestUser 12/05/1990";
    memset(buffer, 0, sizeof(buffer));
    assert(parse_name_manual(line1, buffer) == 1);
    assert(strcmp(buffer, "TestUser") == 0);
    printf("  Test case 1 (Standard): PASSED\n");

    // Test case 2: Multiple spaces between acc_no and name
    char *line2 = "1002    SpacedUser 01/01/2000";
    memset(buffer, 0, sizeof(buffer));
    assert(parse_name_manual(line2, buffer) == 1);
    assert(strcmp(buffer, "SpacedUser") == 0);
    printf("  Test case 2 (Multiple Spaces): PASSED\n");

    // Test case 3: Short name
    char *line3 = "1003 A 01/01/2000";
    memset(buffer, 0, sizeof(buffer));
    assert(parse_name_manual(line3, buffer) == 1);
    assert(strcmp(buffer, "A") == 0);
    printf("  Test case 3 (Short Name): PASSED\n");

    // Test case 4: Malformed (no space)
    char *line4 = "1004NoSpace";
    memset(buffer, 0, sizeof(buffer));
    assert(parse_name_manual(line4, buffer) == 0);
    printf("  Test case 4 (Malformed): PASSED\n");

    printf("All parser correctness tests passed!\n");
    return 0;
}
