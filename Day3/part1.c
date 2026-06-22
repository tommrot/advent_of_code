#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROW_SIZE 200

void compute_joltage(char *number, int *sum);


int main(void){
    int sum = 0;
    FILE *f_ptr = fopen("puzzle.txt", "r");
    if (f_ptr == NULL) return EXIT_FAILURE;

    char *row = malloc(ROW_SIZE);
    while (fgets(row, ROW_SIZE, f_ptr)){
        compute_joltage(row, &sum);
    }
    free(row);
    printf("sum of joltage is: %d\n", sum);
}



void compute_joltage(char *number, int *sum){
    int len = strlen(number);
    int max_ind_first = 0;
    for (int i = 1; i < len - 2; i++){
        if (((int)(number[i] - '0')) > ((int)(number[max_ind_first] - '0'))) max_ind_first = i;
    }
    int first = (int)(number[max_ind_first] - '0');


    int max_ind_second = max_ind_first + 1;
    for (int j = max_ind_second; j < len; j++){
        if (((int)(number[j] - '0')) > ((int)(number[max_ind_second]) - '0')) max_ind_second = j;
    }
    int second = (int)(number[max_ind_second] - '0');


    int value = first * 10 + second;

    *sum += value;
}





