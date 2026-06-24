#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_SIZE 142
#define COL_SIZE 140


int check_forks_for_row(char *row, char *next_row, char *prev_row, int *counter);



int main(void){
    int total_forks_count = 0;
    
    char matrix[COL_SIZE][ROW_SIZE];

    FILE *file_ptr = fopen("forklift.txt", "r");
    if (file_ptr == NULL) EXIT_FAILURE;

    for (int i = 0; i < COL_SIZE; i++){
        if (fgets(matrix[i], ROW_SIZE, file_ptr) == NULL) break;
    }
    fclose(file_ptr);

    char *row = malloc(ROW_SIZE);
    char *prev_row = malloc(ROW_SIZE);
    char *next_row = malloc(ROW_SIZE);


    while (1){
        for (int j = 0; j < ROW_SIZE; j++) prev_row[j] = '.';
        int cycle_forks_count = 0;

        for (int i = 0; i < COL_SIZE; i++){
            strcpy(row, matrix[i]);
            char *original_row = malloc(ROW_SIZE);
            strcpy(original_row, row);

            if (i == COL_SIZE - 1){
                for (int j = 0; j < ROW_SIZE; j++) next_row[j] = '.';
            } else {
                strcpy(next_row, matrix[i + 1]);
            }
            cycle_forks_count += check_forks_for_row(row, next_row, prev_row, &total_forks_count);
            
            strcpy(prev_row, original_row);
            strcpy(matrix[i], row);
        }
        if (cycle_forks_count == 0) break;
    }
    printf("can be removed %d rolls of paper\n", total_forks_count);
}


int check_forks_for_row(char *row, char *next_row, char *prev_row, int *counter){
    int forked = 0;
    char *original_row = malloc(ROW_SIZE);
    strcpy(original_row, row);
    for (int i = 0; i < ROW_SIZE; i++){
        int inside_count = 0;
        if (row[i] == '@'){
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j > ROW_SIZE) continue;
                if (prev_row[j] == '@') inside_count++;
            }
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j == i || j > ROW_SIZE) continue;
                if (original_row[j] == '@') inside_count++;
            }
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j > ROW_SIZE) continue;
                if (next_row[j] == '@') inside_count++;
            }
            if (inside_count < 4) {
                row[i] = '.';
                (*counter)++;
                forked++;
            }
        }
    }
    free(original_row);
    return forked;
}