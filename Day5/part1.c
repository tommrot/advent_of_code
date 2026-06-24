#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FRESH_RANGES 177
#define RANGE_SIZE 100

#define ID_LIST 1000
#define ID_SIZE 50

int is_fresh(char *id_to_check, char **ranges);


int main(void){
    int result = 0;
    FILE *file_ptr = fopen("ingredients.txt", "r");
    if (file_ptr == NULL) exit(0);

    char *fresh_ranges_id[FRESH_RANGES];
    for (int i = 0; i < FRESH_RANGES; i++){
        fresh_ranges_id[i] = malloc(RANGE_SIZE);
    }
    char *id_to_check[ID_LIST];
    for (int i = 0; i < ID_LIST; i++){
        id_to_check[i] = malloc(ID_SIZE);
    }

    for (int i = 0; i < FRESH_RANGES; i++){
        fgets(fresh_ranges_id[i], RANGE_SIZE, file_ptr);
    }
    char *blank_line = malloc(ID_SIZE);
    fgets(blank_line, ID_SIZE, file_ptr);
    free(blank_line);

    for (int i = 0; i < ID_LIST; i++){
        fgets(id_to_check[i], ID_SIZE, file_ptr);
    }


    for (int i = 0; i < ID_LIST; i++){
        result += is_fresh(id_to_check[i], fresh_ranges_id);
        free(id_to_check[i]);
    }
    for (int i = 0; i < FRESH_RANGES; i++){
        free(fresh_ranges_id[i]);
    }

    printf("fresh ingredients are: %d\n", result);
    return 0;
}



int is_fresh(char *id_to_check, char **ranges){
    long long id = atoll(id_to_check);
    for (int i = 0; i < FRESH_RANGES; i++){
        char *range_row = malloc(RANGE_SIZE);   // strtok modify original string, so it's better if we work on a copy
        strcpy(range_row, ranges[i]);
        long long start = atoll(strtok(range_row, "-"));
        long long end = atoll(strtok(NULL, "\n"));
        free(range_row);
        if (start <= id && id <= end) return 1;
    }
    return 0;
}