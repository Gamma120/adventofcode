#pragma once

#include "stdbool.h"

typedef struct _elf
{
    int calories;
    struct _elf *previous;
    struct _elf *next;
} elf;

elf *elf_init();
elf *elf_left_free(elf *elf);
elf *elf_right_free(elf *elf);

bool is_empty(elf *head);

void print_list(elf *head);

elf *insert_first(elf *head, elf *_elf);
elf *insert_last(elf *tail, elf *_elf);

/*
Insert the elf_to_insert before current_elf
*/
void insert(elf *elf_to_insert, elf *current_elf);
