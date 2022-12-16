#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFF_MAX 100


void split(char *string, int len, char *str_1, char *str_2){
    strncpy(str_1,string,len/2);
    str_1[len/2] = '\0';
        
    strncpy(str_2, &string[len / 2], len/2);
    str_2[len/2] = '\0';
}

void common_items(char *str_1, char *str_2, char *dest){
    size_t len_1 = strlen(str_1);
    size_t len_2 = strlen(str_2);

    int cpt = 0;
    for(int i=0; i<len_1; i++){
        if(strchr(dest,str_1[i]) == NULL){ // avoid for the same letter multiple times
        for(int j=0; j<len_2; j++){
            if(str_1[i] == str_2[j]){
                dest[cpt] = str_1[i];
                cpt+=1;
                break;
            }
        }
        }
    }
    //dest[cpt] = '\0';
    return;
}

char common_item_p2(char *str_1, char *str_2, char *str_3){
    char *res_1 = (char *) calloc(BUFF_MAX,sizeof(char));
    common_items(str_1,str_2, res_1);
    char *res_2 = (char *) calloc(BUFF_MAX,sizeof(char));
    common_items(str_1,str_3, res_2);
    char *res_3 = (char *) calloc(BUFF_MAX,sizeof(char));
    common_items(res_1,res_2, res_3);
    
    char ch = res_3[0];

    free(res_1);free(res_2);free(res_3);
    return ch;
}

int get_value(char ch){
    if(isalpha(ch)){
        if(ch >= 97){
            return ch - 96;
        } else if(ch >= 65){
            return ch - 64 + 26;
        }
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]){

    if(argc <3){
        fprintf(stderr, "Usage: %s <file> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *in_path = argv[1]; char *out_path = argv[2];

    FILE * in_ptr = fopen(in_path, "r");

    if(in_ptr == NULL){
        fprintf(stderr, "Error opening %s : %s", in_path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char rucksack[BUFF_MAX];
    char *read;

    int ans_p1 = 0;

    char rucksack_group[3][55];
    int cpt_group = 0;
    int ans_p2 = 0;
    while((read = fgets(rucksack, BUFF_MAX, in_ptr)) != NULL){
        size_t len = strnlen(read, BUFF_MAX) -1; //exclude \n (input must terminate with a \n)

        char part_1[len/2 + 1]; char part_2[len/2 +1];
        
        split(rucksack,len, part_1, part_2);
        char items[2];// = malloc(sizeof(char));
        common_items(part_1, part_2, items);
        
        int item_value = get_value(items[0]);

        if(item_value > 0){
            ans_p1 += item_value;
        } else{
            fprintf(stderr, "An item is not in alphabet: %d", item_value);
            exit(EXIT_FAILURE);
        }

        strncpy(rucksack_group[cpt_group],read,len);
        rucksack_group[cpt_group][len] = '\0';
        char item_p2;
        if(cpt_group == 2){
            item_p2 = common_item_p2(rucksack_group[0], rucksack_group[1], rucksack_group[2]);
            cpt_group = 0;

            int item_p2_value = get_value(item_p2);
            if(item_p2_value > 0){
                ans_p2 += item_p2_value;
            } else{
                fprintf(stderr, "An item is not in alphabet: %d", item_p2);
                exit(EXIT_FAILURE);
            }
        
        } else {
            cpt_group+=1;
        }
    }

    FILE *out_ptr = fopen(out_path, "w");
    fprintf(out_ptr, "%d\n%d",ans_p1,ans_p2);

    fclose(in_ptr); fclose(out_ptr);
    return 0;
}