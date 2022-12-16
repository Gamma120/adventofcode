#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    
    if(argc < 2){
        printf("Missing argument");
        exit(1);
    }
    
    char *file_path = argv[1];
    FILE *fp;
    fp = fopen(file_path, "r");

    if(fp == NULL){
        printf("Error while openning %s", file_path);
        exit(1);
    }

    char ch[2];
    char calories[10];
    int sum = 0;
    int *calories_max = (int *) malloc(sizeof(int)*3);
    int cpt = 0;
    while((*ch = fgetc(fp)) != EOF){
        
        // newline
        if(ch[0] == '\n'){
            // new group
            if(strnlen(calories, 10) == 0){
                calories_max = update_list(sum, calories_max);
                sum = 0; // reset
            } else{
                sum += atoi(calories);

                strncat(calories,"\0", 1);
                calories[0] = '\0';
            }

        } else {
            strncat(calories, ch, 1);
        }
    }

    // last test
    calories_max = update_list(sum, calories_max);

    int ans = 0;
    for(int i=0; i<3; i++){
        ans+=calories_max[i];
    }

    printf("Calories from the elf: %d\n", calories_max[0]);
    printf("Calories from the 3 elves : %d\n",ans);

    free(calories_max);
    fclose(fp);
    return 0;
}