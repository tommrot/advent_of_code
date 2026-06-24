#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS_NUM 177
#define RANGE_SIZE 100

int count_id(char *row, char **fresh_found, int fresh_found_counter);
int check_duplicates(long long num, char **fresh_found, int fresh_found_counter);


int main(void){
    long long total_fresh_id = 0;
    char *fresh_found[ROWS_NUM];
    FILE *file_ptr = fopen("ingredients.txt", "r");
    if (file_ptr == NULL) exit(0);

    char *row = malloc(RANGE_SIZE);

    for (int i = 0; i < ROWS_NUM; i++){
        fgets(row, RANGE_SIZE, file_ptr);
        total_fresh_id += count_id(row, fresh_found, i);
        fresh_found[i] = malloc(RANGE_SIZE);
        strcpy(fresh_found[i], row);
    }
    printf("total fresh ingredients are: %lld\n", total_fresh_id);
}


int count_id(char *row, char **fresh_found, int fresh_found_counter){
    long long counter = 0;
    char *copy = malloc(RANGE_SIZE);
    strcpy(copy, row);
    long long start = atoll(strtok(copy, "-"));
    long long end = atoll(strtok(NULL, "\n"));

    for (long long i = start; i <= end; i++){
        if (check_duplicates(i, fresh_found, fresh_found_counter)) counter++;
    }
    return counter;
}


int check_duplicates(long long num, char **fresh_found, int fresh_found_counter){
    for (int i = 0; i < fresh_found_counter; i++){
        char *copy = malloc(RANGE_SIZE);
        strcpy(copy, fresh_found[i]);
        long long founded_start = atoll(strtok(copy, "-"));
        long long founded_end = atoll(strtok(NULL, "\n"));
        if (founded_start <= num && num <= founded_end) return 0;
    }
    return 1;
}