#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW_SIZE 16

int read_instruction(char *row);
int count_zero_dials(int pos, int shift);
int overflow(int pos);

int main(void){
    int position = 50;
    int counter = 0;
    FILE *file_ptr = fopen("combination.txt", "r");
    if (file_ptr == NULL) return EXIT_FAILURE;
    char *row = malloc(ROW_SIZE);
    while (fgets(row, ROW_SIZE, file_ptr) != NULL){
        int shift = read_instruction(row);
        counter += count_zero_dials(position, shift);
        int new_pos = position + shift;
        if (new_pos < 0 || new_pos > 99) position = overflow(new_pos);
        else position = new_pos;
    }
    printf("key is: %d\n", counter);
}

int read_instruction(char *row){
    char direction = row[0];
    char *val = malloc(strlen(row) - 1);
    for (int i = 1; i < strlen(row) - 1; i++){
        val[i - 1] = row[i];
    }
    return (direction == 'L' ? -(atoi(val)) : atoi(val));
}


int count_zero_dials(int pos, int shift){
    int count = shift / 100;
    if (count < 0) count = -(count);
    int r = shift % 100;
    if (pos != 0){
        int new_pos = pos + r;
        if (new_pos <= 0 || new_pos >= 100) count++;
    }
    return count;
}

int overflow(int pos){
    int r = pos % 100;
    if (r < 0) r += 100;
    return r;
}