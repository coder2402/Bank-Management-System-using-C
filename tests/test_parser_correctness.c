#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

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
};

// Original parsing logic
int parse_sscanf(char *line, struct record *add) {
    return sscanf(line, "%d %s %*d/%*d/%*d %*d %s %*s %lf",
                   &add->acc_no, add->name, add->address, &add->phone);
}

// Optimized parsing logic
int parse_strtok(char *line, struct record *add) {
    char temp_line[1024];
    strncpy(temp_line, line, sizeof(temp_line) - 1);
    temp_line[1023] = '\0';

    char *token;
    char *rest = temp_line;

    // 1. acc_no
    token = strtok(rest, " ");
    if (!token) return 0;
    add->acc_no = atoi(token);

    // 2. name
    token = strtok(NULL, " ");
    if (!token) return 0;
    strncpy(add->name, token, 59);
    add->name[59] = '\0';

    // 3. dob (skip)
    token = strtok(NULL, " ");
    if (!token) return 0;

    // 4. age (skip)
    token = strtok(NULL, " ");
    if (!token) return 0;

    // 5. address
    token = strtok(NULL, " ");
    if (!token) return 0;
    strncpy(add->address, token, 59);
    add->address[59] = '\0';

    // 6. citizenship (skip)
    token = strtok(NULL, " ");
    if (!token) return 0;

    // 7. phone
    token = strtok(NULL, " ");
    if (!token) return 0;
    add->phone = atof(token);

    // Return 4 to match sscanf behavior (number of assigned items)
    return 4;
}

int main() {
    printf("Running parser correctness tests...\n");

    // Test case 1: Standard valid record
    char *line1 = "1001 TestUser 12/05/1990 33 123_Main_St USA 5551234567 Saving 5000.50 01/01/2023\n";
    struct record r1_sscanf = {0}, r1_strtok = {0};

    int res1_sscanf = parse_sscanf(line1, &r1_sscanf);
    int res1_strtok = parse_strtok(line1, &r1_strtok);

    assert(res1_sscanf == 4);
    assert(res1_strtok == 4);
    assert(r1_sscanf.acc_no == r1_strtok.acc_no);
    assert(strcmp(r1_sscanf.name, r1_strtok.name) == 0);
    assert(strcmp(r1_sscanf.address, r1_strtok.address) == 0);
    assert(fabs(r1_sscanf.phone - r1_strtok.phone) < 0.001);

    printf("  Test case 1 (Standard): PASSED\n");

    // Test case 2: Record with different values
    char *line2 = "9999 AnotherUser 01/01/2000 25 456_Side_Rd Canada 1234567890 Current 100.00 05/05/2024\n";
    struct record r2_sscanf = {0}, r2_strtok = {0};

    parse_sscanf(line2, &r2_sscanf);
    parse_strtok(line2, &r2_strtok);

    assert(r2_sscanf.acc_no == r2_strtok.acc_no);
    assert(strcmp(r2_sscanf.name, r2_strtok.name) == 0);
    assert(strcmp(r2_sscanf.address, r2_strtok.address) == 0);
    assert(fabs(r2_sscanf.phone - r2_strtok.phone) < 0.001);

    printf("  Test case 2 (Different Values): PASSED\n");

    // Test case 3: Malformed record (missing fields)
    char *line3 = "1002 IncompleteUser 12/05/1990";
    struct record r3_sscanf = {0}, r3_strtok = {0};

    // sscanf might partially succeed or fail depending on how many match
    // strtok implementation should return 0 if critical fields are missing

    int res3_strtok = parse_strtok(line3, &r3_strtok);
    assert(res3_strtok == 0);

    printf("  Test case 3 (Malformed): PASSED\n");

    printf("All parser correctness tests passed!\n");
    return 0;
}
