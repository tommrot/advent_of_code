#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_SIZE 16

int overflow(int x);
int read_instruction(char *row);
int power_to(int n, int exp);

int main(void){
    
    int counter = 0;
    int position = 50;

    FILE *f_ptr = fopen("combination.txt", "r");
    if (f_ptr == NULL) return EXIT_FAILURE;
    char *row = malloc(ROW_SIZE);
    while (fgets(row, ROW_SIZE, f_ptr)){
        int shift = read_instruction(row);
        int new_pos = position + shift;
        if (new_pos < 0 || new_pos >= 100) position = overflow(new_pos);
        else position = new_pos;
        if (position == 0) counter++;
    }
    
    printf("key is: %d\n", counter);
}


int overflow(int x){
    int r = x % 100;
    if (r < 0) r += 100;
    return r;
}



int read_instruction(char *row){
    char direction = row[0];
    int value = 0;
    for (int i = 1; i < strlen(row) - 1; i++){
        value += ((row[i] - '0') * power_to(10, strlen(row) - 2 - i));
    }
    return (direction == 'L' ? -value : value);
}


int power_to(int n, int exp){
    int res = 1;
    for (int i = 0; i < exp; i++){
        res *= n;
    }
    return res;
}