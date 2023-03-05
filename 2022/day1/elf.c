#include <stdio.h>
#include <stdlib.h>

#include "elf.h"

elf *elf_init()
{
    elf *_elf = (elf *)calloc(1, sizeof(elf));
    _elf->calories = 0;
    _elf->previous = NULL;
    _elf->next = NULL;

    return _elf;
}

elf *elf_left_free(elf *_elf)
{
    if (_elf->previous != NULL)
    {
        fprintf(stderr, "Trying to free an elf that is not at the begin of the linked list.\n");
        exit(EXIT_FAILURE);
    }
    elf *next = _elf->next;
    free(_elf);
    if (next != NULL)
    {
        next->previous = NULL;
    }
    return next;
}

elf *elf_right_free(elf *_elf)
{
    if (_elf->next != NULL)
    {
        fprintf(stderr, "Trying to free an elf that is not at the end of the linked list.\n");
        exit(EXIT_FAILURE);
    }
    elf *previous = _elf->previous;
    free(_elf);
    if (previous != NULL)
    {
        previous->next = NULL;
    }
    return previous;
}

bool is_empty(elf *head)
{
    return head == NULL;
}

void print_list(elf *head)
{

    elf *cursor = head;
    while (cursor != NULL)
    {
        printf("%i\n", cursor->calories);
        cursor = cursor->next;
    }
}

elf *insert_first(elf *head, elf *elf)
{
    elf->next = head;
    head->previous = elf;
    return elf;
}

elf *insert_last(elf *tail, elf *elf)
{
    tail->next = elf;
    elf->previous = tail;
    return elf;
}

void insert(elf *elf_to_insert, elf *current_elf)
{
    current_elf->previous->next = elf_to_insert;
    elf_to_insert->previous = current_elf->previous;
    elf_to_insert->next = current_elf;
    current_elf->previous = elf_to_insert;
}