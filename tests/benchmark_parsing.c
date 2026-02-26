#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITERATIONS 1000000

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

int main() {
    char line[] = "1001 TestUser 12/05/1990 33 123_Main_St USA 5551234567 Saving 5000.50 01/01/2023";

    clock_t start, end;
    double cpu_time_used;
    int i;
    int count = 0;

    // Benchmark 1: Original complex sscanf
    start = clock();
    for (i = 0; i < ITERATIONS; i++) {
        if (sscanf(line, "%d %s %*d/%*d/%*d %*d %s %*s %lf",
                   &add.acc_no, add.name, add.address, &add.phone) == 4) {
            count++;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Original sscanf time: %f seconds (count=%d)\n", cpu_time_used, count);

    // Benchmark 2: Simplified sscanf (using %*s to skip fields)
    count = 0;
    start = clock();
    for (i = 0; i < ITERATIONS; i++) {
        if (sscanf(line, "%d %s %*s %*s %s %*s %lf",
                   &add.acc_no, add.name, add.address, &add.phone) == 4) {
            count++;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Simplified sscanf time: %f seconds (count=%d)\n", cpu_time_used, count);

    // Benchmark 3: strtok (Manual parsing)
    // Note: strtok modifies the string, so we need a copy each time
    count = 0;
    start = clock();
    char temp_line[256];
    for (i = 0; i < ITERATIONS; i++) {
        strcpy(temp_line, line);
        char *token;

        token = strtok(temp_line, " "); // acc_no
        if (!token) continue;
        add.acc_no = atoi(token);

        token = strtok(NULL, " "); // name
        if (!token) continue;
        strcpy(add.name, token);

        token = strtok(NULL, " "); // dob (skip)
        if (!token) continue;

        token = strtok(NULL, " "); // age (skip)
        if (!token) continue;

        token = strtok(NULL, " "); // address
        if (!token) continue;
        strcpy(add.address, token);

        token = strtok(NULL, " "); // citizenship (skip)
        if (!token) continue;

        token = strtok(NULL, " "); // phone
        if (!token) continue;
        add.phone = atof(token);

        count++;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("strtok time: %f seconds (count=%d)\n", cpu_time_used, count);

    return 0;
}
