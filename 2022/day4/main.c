#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_MAX 100


void extract_section(char *section_range, int *sections){
    char *section_inf = strtok(section_range,"-");
    char *section_sup = strtok(NULL,"-");
    sections[0] = atoi(section_inf);
    sections[1] = atoi(section_sup);
    return;
}

int iscontained(int *section_1, int *section_2){
    // section 1 is contained in section 2
    if(section_1[0]>= section_2[0] & section_1[1]<=section_2[1]){
        return true;
    } 
    // section 2 is contained in section 1
    else if(section_2[0]>= section_1[0] & section_2[1]<=section_1[1]){
        return true;
    } else{
        return false;
    }
}

int isoverlapped(int *section_1, int *section_2){
    // return false when section 1 contains section 2
    // section 2 contains section 1 inf edge
    if(section_1[0]>=section_2[0] & section_1[0]<=section_2[1]){
        return true;
    }
    // section 2 contains section 1 sup edge
    else if(section_1[1]>=section_2[0] & section_1[1]<=section_2[1]){
        return true;
    } else{
        return false;
    }
}

int main(int argc, char *argv[]){
    /*
    argv[1]: input file path
    argv[2]: output file path
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
    char *read;
    int ans_p1 = 0;
    int ans_p2 =0;
    while((read = fgets(line,BUFF_MAX,in_ptr)) != NULL){
        size_t len = strlen(read) -1; // doesn't count \n
        char *section_range_1 = strtok(read,",");
        char *section_range_2 = strtok(NULL,",");
        int section_1[2]; int section_2[2];
        extract_section(section_range_1, section_1);
        extract_section(section_range_2, section_2);

        if(iscontained(section_1,section_2)){
            ans_p1++;
            ans_p2++;
        } else if(isoverlapped(section_1,section_2)){
            ans_p2++;
        }
    }

    out_ptr = fopen(out_path, "w");
    fprintf(out_ptr,"%d\n%d\n", ans_p1, ans_p2);

    fclose(in_ptr);
    return EXIT_SUCCESS;
}