#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void invalids_id_in_range(long long start, long long end, long long *sum);
int is_invalid(long long num);
int power_to(int n, int exp);


int main(void){
    
    long long sum = 0;
 
    FILE *file_ptr = fopen("id_range_list.txt", "r");
    if (file_ptr == NULL) return EXIT_FAILURE;
    
    char *row = malloc(sizeof(char) * 600);
    if (fgets(row, 600, file_ptr)){
        char *token = strtok(row, "-,\n");
        
        while (token != NULL){
            long long start = atoll(token);
            
            token = strtok(NULL, ",\n");   //first parameter of strtok NULL continues from last stop in string
            if (token == NULL) break; 
            long long end = atoll(token);

            invalids_id_in_range(start, end, &sum);

            token = strtok(NULL, "-");
        }
    }
    free(row);
    fclose(file_ptr);

    printf("sum of invalid id is: %lld\n", sum);
}



void invalids_id_in_range(long long start, long long end, long long *sum){
    for (long long i = start; i <= end; i++){
        if (is_invalid(i)) ((*sum) += i);
    }
}

int is_invalid(long long num){
    int digs_counter = 0;
    long long n = num;
    while (n > 0){
        n /= 10;
        digs_counter++;
    }
    if (digs_counter % 2 == 1) return 0;
    else if ((num % power_to(10, digs_counter / 2)) == (num / power_to(10, digs_counter / 2))) return 1;
    return 0;    
}


int power_to(int n, int exp){
    int res = 1;
    for (int i = 0; i < exp; i++){
        res *= n;
    }
    return res;
}


