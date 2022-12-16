#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    /*
    argv[1] : input_file
    */

    if(argc < 2){
        printf("Missing arguments\n");
        exit(1);
    }

    char *in_path = argv[1];
    FILE *in_ptr = fopen(in_path, "r");
    if(in_ptr == NULL){
        printf("Error while opening %s", in_path);
        exit(1);
    }

    char ch[1];
    int score = 0;
    char op_hand;
    while((*ch = fgetc(in_ptr)) != EOF){
        switch (*ch)
        {
        case 'X': // LOOSE
            if(op_hand == 'A'){
                score += Z;
            } else if(op_hand == 'B'){
                score += X;
            } else {
                score += Y;
            }
            break;
        case 'Y': // DRAW
            if(op_hand == 'A'){
                score += X;
            } else if(op_hand == 'B'){
                score += Y;
            } else {
                score += Z;
            }
            score += DRAW;
            break;
        case 'Z': // WIN
            if(op_hand == 'A'){
                score += Y;
            } else if(op_hand == 'B'){
                score += Z;
            } else {
                score += X;
            }
            score += WIN;
            break;
        case 'A': case 'B': case 'C': // opponent hand
            op_hand = *ch;
            break;
        default: // skip new line and space
            break;
        }
    }

    printf("Score: %d", score);

    fclose(in_ptr);
}