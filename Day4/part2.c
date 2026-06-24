#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROW_SIZE 142
#define COL_SIZE 140

int check_forklift_for_row(char *row, char *prev_row, char *next_row, int *counter);

int main(void){
    int counter = 0;
    char matrix[COL_SIZE][ROW_SIZE];
    char mod_matrix[COL_SIZE][ROW_SIZE];
    FILE *file_ptr = fopen("forklift.txt", "r");
    if (file_ptr == NULL) return EXIT_FAILURE;

    char *prev_row = malloc(ROW_SIZE);
    char *row = malloc(ROW_SIZE);
    char *next_row = malloc(ROW_SIZE);  
    char *original_row = malloc(ROW_SIZE);  
    for (int i = 0; i < 140; i++){
        fgets(matrix[i], ROW_SIZE, file_ptr);
    }

    while (1){
        int forks_found = 0;
        strcpy(row, matrix[0]);
        for (int j = 0; j < ROW_SIZE; j++) prev_row[j] = '.';
        for (int i = 0; i < COL_SIZE; i++){
            strcpy(original_row, row);
            if (i == 139){
                for (int j = 0; j < ROW_SIZE; j++){
                    next_row[j] = '.';
                }
            }  
            else {
                strcpy(next_row, matrix[i+1]);
            }

            forks_found += check_forklift_for_row(row, prev_row, next_row, &counter);
            strcpy(matrix[i], row);
            strcpy(prev_row, original_row);
            strcpy(row, next_row);
        }

        if (forks_found == 0) break;
    }
    printf("sum is: %d\n", counter);
    
}



int check_forklift_for_row(char *row, char *prev_row, char *next_row, int *counter){
    int forklist_found = 0;
    for (int i = 0; i < ROW_SIZE; i++){
        int inside_count = 0;
        if (row[i] == '@'){
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j >= ROW_SIZE) continue;
                if (prev_row[j] == '@') inside_count++;
            }
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j == i || j >= ROW_SIZE) continue;
                if (row[j] == '@') inside_count++;
            }
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j >= ROW_SIZE) continue;
                if (next_row[j] == '@') inside_count++;
            }
            if (inside_count < 4){
                forklist_found++;
                (*counter)++;
                 row[i] = '.';
            }
        }
    }
    return forklist_found;
}