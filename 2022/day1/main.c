#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "main.h"
#include "elf.h"

#define BUFF_MAX 15
#define TOP 3

int main(int argc, char *argv[])
{
    /*
    argv[1] : input file
    argv[2] : output file
    */
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <file> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *in_path = argv[1];
    char *out_path = argv[2];
    FILE *in_ptr, *out_ptr;
    in_ptr = fopen(in_path, "r");

    if (in_ptr == NULL)
    {
        fprintf(stderr, "Error while opening %s : %s\n", in_path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char line[BUFF_MAX];

    linked_list *l = list_init(TOP);
    int calories = 0;
    while (fgets(line, BUFF_MAX, in_ptr) != NULL)
    {
        if (line[0] == '\n')
        {
            insert(l, calories);
            calories = 0;
        }
        else
        {
            calories += atoi(line);
        }
    }

    elf *top_elf = l->head;
    int ans_p1 = top_elf->calories;
    int ans_p2 = 0;
    for (int j = 0; j < TOP; j++)
    {
        ans_p2 += top_elf->calories;
        top_elf = top_elf->next;
    }

    out_ptr = fopen(out_path, "w");
    if (out_ptr == NULL)
    {
        fprintf(stderr, "Error while opening %s : %s\n", out_path, strerror(errno));
        fprintf(stdout, "%d\n%d", ans_p1, ans_p2);
    }
    else
    {
        fprintf(out_ptr, "%d\n%d", ans_p1, ans_p2);
        fclose(out_ptr);
    }
    list_free(l);
    fclose(in_ptr);
    return EXIT_SUCCESS;
}