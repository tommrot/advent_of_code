#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_SIZE 200

void compute_joltage(char *row, long long *sum);

int main(void){
    long long sum = 0;
    char *row = malloc(ROW_SIZE);
    FILE *f_ptr = fopen("puzzle.txt", "r");
    if (f_ptr == NULL) return EXIT_FAILURE;
    
    while (fgets(row, ROW_SIZE, f_ptr)){
        compute_joltage(row, &sum);
    }
    free(row);
    printf("sum of joltage is: %lld\n", sum);
}


void compute_joltage(char *row, long long *sum) {
    int len = strlen(row);
    if (row[len - 1] == '\n') len--;  // rimuovi newline se presente

    char *result = malloc(12 + 1);
    int pos = 0;  // da dove possiamo iniziare a cercare

    for (int slot = 0; slot < 12; slot++) {
        int remaining_needed = 12 - slot - 1;
        int search_end = len - remaining_needed - 1;  // ultimo indice valido

        int best = pos;
        for (int j = pos + 1; j <= search_end; j++) {
            if (row[j] > row[best]) {
                best = j;
            }
        }

        result[slot] = row[best];
        pos = best + 1;
    }
    result[12] = '\0';

    *sum += atoll(result);
    free(result);
}