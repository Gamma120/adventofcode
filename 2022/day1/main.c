#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "elf.h"

#define BUFF_MAX 15
#define TOP 3 // size of the list

void update_rank(elf **head, elf **tail, elf *current_elf)
{
    if (is_empty(*head) || is_empty(*tail))
    {
        fprintf(stderr, "The list has been lost. Elves are free!\n");
        exit(EXIT_FAILURE);
    }
    if (current_elf->calories < (*tail)->calories)
    { // the elf doesn't carry enought calories to be in the list
    }
    else
    {
        if (current_elf->calories > (*head)->calories)
        { // He is the new head
            *head = insert_first(*head, current_elf);
        }
        else
        { // scan the list to find the place of this elf
            int i = 0;
            elf *cursor = (*head);
            while (i < TOP)
            {
                if (current_elf->calories > cursor->calories)
                {
                    insert(current_elf, cursor);
                    break;
                }
                cursor = cursor->next;
                i++;
            }
        }
        // We drop the last elf of the list, so the size of the list is constant
        *tail = elf_right_free(*tail);
    }
}

void init_rank(elf **head, elf **tail, elf *current_elf)
{

    if (is_empty(*head))
    { // First elf in the list
        *head = current_elf;
        *tail = current_elf;
    }
    else
    { // scan the list to find the place of this elf
        int i = 0;
        elf *cursor = (*head);
        while (cursor != NULL)
        {
            if (current_elf->calories > cursor->calories)
            {
                if (cursor == *head)
                {
                    *head = insert_first(*head, current_elf);
                }
                else
                {
                    insert(current_elf, cursor);
                }
                break;
            }
            cursor = cursor->next;
            i++;
        }
        if (cursor == NULL)
        { // This elf has the lowest in calories, append at the end of the list
            *tail = insert_last(*tail, current_elf);
        }
    }
}

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
        fprintf(stderr, "Error opening %s : %s", in_path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char line[BUFF_MAX];

    elf **head = calloc(1, sizeof(elf *)); // begining of the list
    elf **tail = calloc(1, sizeof(elf *)); // end of the list

    elf *current_elf = elf_init();

    int i = 0;
    // Intialization of the top elves list
    while (i < TOP && fgets(line, BUFF_MAX, in_ptr) != NULL)
    {
        if (line[0] == '\n')
        {
            init_rank(head, tail, current_elf);
            current_elf = elf_init();
            i++;
        }
        else
        {
            current_elf->calories += atoi(line);
        }
    }

    while (fgets(line, BUFF_MAX, in_ptr) != NULL)
    {
        if (line[0] == '\n')
        {
            update_rank(head, tail, current_elf);
            current_elf = elf_init();
        }
        else
        {
            current_elf->calories += atoi(line);
        }
    }

    elf *top_elf = *head;
    int ans_p1 = top_elf->calories;
    int ans_p2 = 0;
    for (int j = 0; j < TOP; j++)
    {
        ans_p2 += top_elf->calories;
        top_elf = top_elf->next;
    }

    out_ptr = fopen(out_path, "w");
    fprintf(out_ptr, "%d\n%d", ans_p1, ans_p2);

    while (top_elf != NULL)
    {
        top_elf = elf_left_free(top_elf);
    }

    fclose(in_ptr);
    fclose(out_ptr);
    return EXIT_SUCCESS;
}