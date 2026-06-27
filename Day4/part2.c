#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_SIZE 142
#define COLUMS 140

int main(void){
    int total_counter = 0;
    FILE *file_ptr = fopen("forklift.txt", "r");
    if (file_ptr == NULL) exit(0);

    char matrix[COLUMS][ROW_SIZE];

    char row[ROW_SIZE];
    char prev_row[ROW_SIZE];
    char next_row[ROW_SIZE];

    for (int i = 0; i < COLUMS; i++){
        fgets(matrix[i], ROW_SIZE, file_ptr);
    }

    while (1){
        int added_for_matrix = 0;
        for (int i = 0; i < COLUMS; i++){
            strcpy(row, matrix[i]);
            char original_row[ROW_SIZE];
            strcpy(original_row, row);
            if (i == 0) {
                for (int j = 0; j < ROW_SIZE; j++) prev_row[j] = '.';
            } else {
                strcpy(prev_row, matrix[i - 1]);
            }
            if (i == COLUMS - 1) {
                for (int j = 0; j < ROW_SIZE; j++) next_row[j] = '.';
            } else {
                strcpy(next_row, matrix[i + 1]);
            }
            added_for_matrix += forklist_check_for_row(row, prev_row, next_row);  
            
            strcpy(prev_row, original_row);
            strcpy(matrix[i], row);
        }
        if (added_for_matrix == 0) break;
    }
}



int forklist_check_for_row(char *row, char *prev_row, char* next_row){
    int counter = 0;
    for (int i = 0; i < ROW_SIZE; i++){
        if (row[i] == '@'){
            int internal_counter = 0;
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j >= ROW_SIZE ) continue;
                if (prev_row[j] == '@') internal_counter++;
            }
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j == i || j >= ROW_SIZE) continue;
                if (row[j] == '@') internal_counter++;
            }
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j >= ROW_SIZE) continue;
                if (next_row[j] == '@') internal_counter++;
            }
            if (internal_counter < 4) {row[i] = '.'; counter++;}
        }
    }
    return counter;
}


