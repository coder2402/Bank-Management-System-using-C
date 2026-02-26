#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Mock structures
struct date {
    int month, day, year;
};

struct record {
    char name[60];
    int acc_no, age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
} add;

// Simulate file content
#define NUM_RECORDS 100000
char *file_content[NUM_RECORDS];

void init_data() {
    for (int i = 0; i < NUM_RECORDS; i++) {
        file_content[i] = strdup("1001 TestUser 12/05/1990 33 123_Main_St USA 5551234567 Saving 5000.50 01/01/2023\n");
    }
}

void cleanup_data() {
    for (int i = 0; i < NUM_RECORDS; i++) {
        free(file_content[i]);
    }
}

int main() {
    init_data();

    char line_buffer[1024];
    clock_t start, end;
    double cpu_time_used;
    int count = 0;

    // Method 1: Original sscanf
    count = 0;
    start = clock();
    for (int i = 0; i < NUM_RECORDS; i++) {
        strcpy(line_buffer, file_content[i]); // Simulate fgets

        if (sscanf(line_buffer, "%d %s %*d/%*d/%*d %*d %s %*s %lf",
                   &add.acc_no, add.name, add.address, &add.phone) == 4) {
            // Simulate printf logic (check values)
             if (add.acc_no == 1001) count++;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Original sscanf: %f seconds (count=%d)\n", cpu_time_used, count);

    // Method 2: strtok
    count = 0;
    start = clock();
    for (int i = 0; i < NUM_RECORDS; i++) {
        strcpy(line_buffer, file_content[i]); // Simulate fgets

        char *token;
        char *rest = line_buffer;

        // 1. acc_no
        token = strtok(rest, " ");
        if(!token) continue;
        add.acc_no = atoi(token);

        // 2. name
        token = strtok(NULL, " ");
        if(!token) continue;
        strncpy(add.name, token, 59);
        add.name[59] = '\0';

        // 3. dob (skip)
        token = strtok(NULL, " ");
        if(!token) continue;

        // 4. age (skip)
        token = strtok(NULL, " ");
        if(!token) continue;

        // 5. address
        token = strtok(NULL, " ");
        if(!token) continue;
        strncpy(add.address, token, 59);
        add.address[59] = '\0';

        // 6. citizenship (skip)
        token = strtok(NULL, " ");
        if(!token) continue;

        // 7. phone
        token = strtok(NULL, " ");
        if(!token) continue;
        add.phone = atof(token);

        // Simulate printf logic
        if (add.acc_no == 1001) count++;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Optimized strtok: %f seconds (count=%d)\n", cpu_time_used, count);

    cleanup_data();
    return 0;
}
