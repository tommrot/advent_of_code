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
    char *result = malloc(sizeof(char) * 13);
    int position = 0;
    int len = strlen(row);
    if (row[len - 1] == '\n') len--;
    
    for (int i = 0; i < 12; i++){
        int least_needed = 12 - i - 1;
        int stop = len - 1 - least_needed;
        int best = position;
        for (int j = position; j <= stop; j++){
            if (row[j] > row[best]) best = j;
        }
        result[i] = row[best];
        position = best + 1;
    }
    result[12] = '\0';
    *sum += atoll(result);
    free(result);
}