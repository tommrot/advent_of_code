#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Ingredient{
    char *row;
    long long start;
    long long end;
} Ingredient;


#define ROWS_NUM 177
#define RANGE_SIZE 100


int compare_starts(const void *a, const void *b);
int merge_intervals(Ingredient *items);


int main(void){
    long long total = 0;
    Ingredient items[ROWS_NUM];
    char buff[RANGE_SIZE];

    FILE *file_ptr = fopen("ingredients.txt", "r");
    for (int i = 0; i < ROWS_NUM; i++){
        items[i].row = malloc(RANGE_SIZE);
        fgets(buff, RANGE_SIZE, file_ptr);
        strcpy(items[i].row, buff);
        items[i].start = atoll(strtok(buff, "-"));
        items[i].end = atoll(strtok(NULL, "\n"));
    }
    fclose(file_ptr);
    qsort(items, ROWS_NUM, sizeof(Ingredient), compare_starts);

    int counter = merge_intervals(items);
    for (int i = 0; i < counter; i++){
        total += (items[i].end - items[i].start + 1);
    }
    printf("ingredients are: %lld\n", total);
    
}



int compare_starts(const void *a, const void *b){   //compare function inside qsort is declared as int compare(const void *a, const void *b); 
    const Ingredient *a_ptr = (const Ingredient *) a;
    const Ingredient *b_ptr = (const Ingredient *) b;
    
    if (a_ptr->start > b_ptr->start) return 1;
    if (a_ptr->start < b_ptr->start) return -1;
    return 0;
}


int merge_intervals(Ingredient *items){
    int j = 0;
    for (int i = 1; i < ROWS_NUM; i++){
        if (items[j].end >= items[i].start){
            if (items[i].end > items[j].end) items[j].end = items[i].end;
            free(items[i].row);
            items[i].row = NULL;
        } else {
            j++;
            items[j] = items[i];
        }
    }
    return j + 1;  //j is index, but we want to pass length
}