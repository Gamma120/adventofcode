#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_MAX 15

int *update_list(int num, int *max_list){
    int len = 3;
    int pos = 0;
    
    for(int i=0; i<len; i++){
        if(num < max_list[i]){
            pos++;
        }
    }

    if(pos<=2){
        max_list = decrease_rank(max_list, pos);
        max_list[pos] = num;
    }

    return max_list;
}

int *decrease_rank(int *list, int position){
    int len = 3;
    for(int i=len-2; i>=position; i--){
        list[i+1] = list[i];
    }
    return list;
}

int main(int argc, char *argv[]){
    /*
    argv[1] : input file
    argv[2] : output file
    */
    if(argc < 3){
        fprintf(stderr, "Usage: %s <file> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *in_path = argv[1]; char *out_path = argv[2];
    FILE *in_ptr, *out_ptr;
    in_ptr = fopen(in_path, "r");

    if(in_ptr == NULL){
        fprintf(stderr, "Error opening %s : %s", in_path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char line[BUFF_MAX];
    int sum = 0;
    int *calories_max = (int *) malloc(sizeof(int)*3);
    
    while(fgets(line,BUFF_MAX,in_ptr) != NULL){
        // new elf
        if(line[0] == '\n'){
            // check if elf is in top 3
            calories_max = update_list(sum, calories_max);
            sum = 0;
        }else{
            sum += atoi(line);
        }
    }

    int ans_p1 = calories_max[0];
    int ans_p2 = calories_max[0]+calories_max[1]+calories_max[2];

    out_ptr = fopen(out_path, "w");
    fprintf(out_ptr,"%d\n%d", ans_p1, ans_p2);
    
    free(calories_max);
    fclose(in_ptr); fclose(out_ptr);
    return EXIT_SUCCESS;
}