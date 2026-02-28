#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITERATIONS 1000000

#ifdef _WIN32
#define strcmpi _stricmp
#else
#define strcmpi strcasecmp
#endif

int main() {
    char line[] = "  1001 TestUser 12/05/1990 33 123_Main_St USA 5551234567 Saving 5000.50 01/01/2023\n";
    char check_name[] = "TestUser";

    clock_t start, end;
    double cpu_time_used;
    int count = 0;

    // Benchmark 1: sscanf
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        char read_name[60];
        if (sscanf(line, "%*d %59s", read_name) == 1 && strcmpi(read_name, check_name) == 0) {
            count++;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Original sscanf time: %f seconds (count=%d)\n", cpu_time_used, count);

    // Benchmark 2: manual parsing
    count = 0;
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        char read_name[60];
        int match = 0;
        char *ptr = line;

        // Skip leading spaces
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        // Skip first word (acc_no)
        while (*ptr != ' ' && *ptr != '\t' && *ptr != '\0') ptr++;
        // Skip spaces between acc_no and name
        while (*ptr == ' ' || *ptr == '\t') ptr++;

        if (*ptr != '\0') {
            char *name_end = ptr;
            while (*name_end != ' ' && *name_end != '\t' && *name_end != '\0' && *name_end != '\n') name_end++;
            int len = name_end - ptr;
            if (len > 0 && len < 60) {
                memcpy(read_name, ptr, len);
                read_name[len] = '\0';
                if (strcmpi(read_name, check_name) == 0) {
                    match = 1;
                }
            }
        }
        if (match) {
            count++;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("manual parsing time: %f seconds (count=%d)\n", cpu_time_used, count);

    return 0;
}
