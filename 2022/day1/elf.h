#pragma once

#include "stdbool.h"

typedef struct _elf
{
    int calories;
    struct _elf *previous;
    struct _elf *next;
} elf;

typedef struct linked_list
{
    int length_max;
    int length;
    elf *head;
    elf *tail;
} linked_list;

elf *elf_init();
linked_list *list_init(int length_max);
void list_free(linked_list *l);
void left_free(linked_list *l);
void right_free(linked_list *l);

bool is_empty(linked_list *l);

void print_list(linked_list *l);

void prepend(linked_list *l, elf *_elf);
void append(linked_list *l, elf *_elf);
void insert(linked_list *l, int calories);
