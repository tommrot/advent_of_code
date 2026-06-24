#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROW_SIZE 142

void check_forklist(char *row, char *next_row, char *prev_row, int *counter);

int main(void){
    int counter = 0;
    FILE *f_ptr = fopen("forklift.txt", "r");
    if (f_ptr == NULL) return EXIT_FAILURE;
    
    char *row = malloc(sizeof(char) * ROW_SIZE);
    char *next_row = malloc(sizeof(char) * ROW_SIZE);
    char *prev_row = NULL;
    fgets(row, ROW_SIZE, f_ptr);
    int is_last = 0;

    while (row != NULL && is_last != 1){
        if (prev_row == NULL){
            prev_row = malloc(sizeof(char) * ROW_SIZE);
            for (int i = 0; i < ROW_SIZE; i++) prev_row[i] = '.';
        }
        
        if (fgets(next_row, ROW_SIZE, f_ptr) == NULL){
            for (int i = 0; i < ROW_SIZE; i++) next_row[i] = '.';
            is_last = 1;
        }
        
        check_forklist(row, next_row, prev_row, &counter);
        strcpy(prev_row, row);
        strcpy(row, next_row);
    }
    printf("forkslist counter is: %d\n", counter);
}



void check_forklist(char *row, char *next_row, char *prev_row, int *counter){
    int inside_count = 0;
    for (int i = 0; i < ROW_SIZE; i++){
        if (row[i] == '@'){
            inside_count = 0;
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j > ROW_SIZE) continue;
                if (prev_row[j] == '@') inside_count++;
            }
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j == i || j > ROW_SIZE) continue;
                if (row[j] == '@') inside_count++;
            }           
            for (int j = i - 1; j <= i + 1; j++){
                if (j < 0 || j > ROW_SIZE) continue;
                if (next_row[j] == '@') inside_count++; 
            }
            if (inside_count < 4) (*counter)++;
        }
    }
}