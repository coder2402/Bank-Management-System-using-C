#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#ifdef _WIN32
#include <strings.h>
#define strcmpi strcasecmp
#else
#include <strings.h>
#define strcmpi strcasecmp
#endif

// Original implementation using sscanf
int parse_name_sscanf(const char *line, char *name_buffer) {
    return sscanf(line, "%*d %59s", name_buffer);
}

// Optimized implementation using manual parsing
int parse_name_manual(const char *line, char *name_buffer) {
    const char *ptr_start = strchr(line, ' ');
    if (ptr_start) {
        ptr_start++; // Skip space
        const char *ptr_end = strchr(ptr_start, ' ');
        if (ptr_end) {
            size_t len = ptr_end - ptr_start;
            if (len < 60) {
                memcpy(name_buffer, ptr_start, len);
                name_buffer[len] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    printf("Benchmarking name parsing strategies...\n");

    const int ITERATIONS = 10000000;
    const char *test_line = "123456 TestUser 12/05/1990 33 123_Main_St USA 5551234567 Saving 5000.50 01/01/2023\n";
    char buffer[60];

    // Correctness Check
    memset(buffer, 0, sizeof(buffer));
    parse_name_sscanf(test_line, buffer);
    printf("sscanf result: '%s'\n", buffer);
    assert(strcmp(buffer, "TestUser") == 0);

    memset(buffer, 0, sizeof(buffer));
    parse_name_manual(test_line, buffer);
    printf("manual result: '%s'\n", buffer);
    assert(strcmp(buffer, "TestUser") == 0);

    printf("Correctness verified.\n");

    // Benchmark sscanf
    clock_t start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        parse_name_sscanf(test_line, buffer);
        // preventative optimization against compiler optimizing away the loop
        if (buffer[0] == 'X') printf("Impossible");
    }
    clock_t end = clock();
    double time_sscanf = (double)(end - start) / CLOCKS_PER_SEC;
    printf("sscanf time: %.4f seconds\n", time_sscanf);

    // Benchmark manual
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        parse_name_manual(test_line, buffer);
        if (buffer[0] == 'X') printf("Impossible");
    }
    end = clock();
    double time_manual = (double)(end - start) / CLOCKS_PER_SEC;
    printf("manual time: %.4f seconds\n", time_manual);

    printf("Speedup: %.2fx\n", time_sscanf / time_manual);

    return 0;
}
