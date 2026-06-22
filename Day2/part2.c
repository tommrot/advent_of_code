#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void invalid_id_in_range(long long start, long long end, long long *sum);
int is_invalid_id(long long n);

int main(void){
    long long sum = 0;
    FILE *f_ptr = fopen("id_range_list.txt", "r");
    if (f_ptr == NULL) return EXIT_FAILURE;
    char *row = malloc(600 *sizeof(char));
    if (fgets(row, 600, f_ptr)){
        char *token = strtok(row, "-");
        while (token != NULL){
            long long start = atoll(token);
            token = strtok(NULL, ",");
            if (token == NULL) return EXIT_FAILURE;
            long long end = atoll(token);
            invalid_id_in_range(start, end, &sum);
            token = strtok(NULL, "-");
        }
    }
    printf("sum of invalid id: %lld\n", sum);
}



void invalid_id_in_range(long long start, long long end, long long *sum){
    for (long long i = start; i <= end; i++){
        if (is_invalid_id(i)) *sum += i;
    }
}

int is_invalid(long long n){
    char buf[32];
    sprintf(buf, "%lld", n);
    int len = strlen(buf);
    for (int L = 1; L < len; L++){
        if (len % L != 0) continue;
        int intervals = len / L;
        int looks_invalid = 1;
        for (int i = 1; i < intervals && looks_invalid == 1; i++){
            for (int j = 0; j < L; j++){
                if (buf[j] != buf[i * L + j]) {looks_invalid = 0; break;}
            }
        }   
        if (looks_invalid == 1) return 1;     
    }
    return 0;
}