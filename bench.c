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

void parse_pointers(char *line_buffer) {
    char *p = line_buffer;
    char *end;

    add.acc_no = strtol(p, &p, 10);

    while (*p == ' ') p++;
    end = strchr(p, ' ');
    if (!end) return;
    size_t len = end - p;
    if (len > 59) len = 59;
    memcpy(add.name, p, len);
    add.name[len] = '\0';
    p = end;

    while (*p == ' ') p++;
    p = strchr(p, ' '); if (!p) return;

    while (*p == ' ') p++;
    p = strchr(p, ' '); if (!p) return;

    while (*p == ' ') p++;
    end = strchr(p, ' ');
    if (!end) return;
    len = end - p;
    if (len > 59) len = 59;
    memcpy(add.address, p, len);
    add.address[len] = '\0';
    p = end;

    while (*p == ' ') p++;
    p = strchr(p, ' '); if (!p) return;

    add.phone = strtod(p, NULL);
}

int main() {
    const char *data = "12345 JohnDoe 1/1/1990 30 123MainSt US 5551234 Saving 1000.0 1/1/2020\n";
    int iters = 1000000;

    char buf[1024];

    clock_t start = clock();
    for (int i = 0; i < iters; i++) {
        strcpy(buf, data);
        parse_strtok(buf);
    }
    clock_t end = clock();
    printf("strtok: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < iters; i++) {
        strcpy(buf, data);
        parse_pointers(buf);
    }
    end = clock();
    printf("pointers: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
