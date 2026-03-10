#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct {
    int acc_no;
    char name[60];
    char address[60];
    double phone;
} add;

void parse_sscanf(const char *line_buffer) {
    int dummy_month, dummy_day, dummy_year, dummy_age, dummy_m2, dummy_d2, dummy_y2;
    char dummy_citizenship[15], dummy_type[10];
    float dummy_amt;

    sscanf(line_buffer, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
           &add.acc_no, add.name, &dummy_month, &dummy_day, &dummy_year,
           &dummy_age, add.address, dummy_citizenship, &add.phone, dummy_type,
           &dummy_amt, &dummy_m2, &dummy_d2, &dummy_y2);
}

void parse_strtok(char *line_buffer) {
    char *token;
    char *rest = line_buffer;

    token = strtok(rest, " ");
    if (!token) return;
    add.acc_no = atoi(token);

    token = strtok(NULL, " ");
    if (!token) return;
    strncpy(add.name, token, 59);
    add.name[59] = '\0';

    if (!strtok(NULL, " ")) return;
    if (!strtok(NULL, " ")) return;

    token = strtok(NULL, " ");
    if (!token) return;
    strncpy(add.address, token, 59);
    add.address[59] = '\0';

    if (!strtok(NULL, " ")) return;

    token = strtok(NULL, " ");
    if (!token) return;
    add.phone = atof(token);
}

int main() {
    const char *data = "12345 JohnDoe 1/1/1990 30 123MainSt US 5551234 Saving 1000.0 1/1/2020\n";
    int iters = 1000000;

    char buf[1024];

    clock_t start = clock();
    for (int i = 0; i < iters; i++) {
        strcpy(buf, data);
        parse_sscanf(buf);
    }
    clock_t end = clock();
    printf("sscanf: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < iters; i++) {
        strcpy(buf, data);
        parse_strtok(buf);
    }
    end = clock();
    printf("strtok: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
