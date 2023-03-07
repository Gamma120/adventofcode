#include <stdio.h>
#include <stdlib.h>

#include "elf.h"

elf *elf_init(int calories)
{
    elf *_elf = (elf *)calloc(1, sizeof(elf));
    _elf->calories = calories;
    _elf->previous = NULL;
    _elf->next = NULL;

    return _elf;
}

linked_list *list_init(int length_max)
{
    linked_list *l = (linked_list *)calloc(1, sizeof(linked_list));
    l->length_max = length_max;
    l->length = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

void list_free(linked_list *l)
{
    while (l->length > 0)
    {
        elf *head = l->head;
        l->head = head->next;
        free(head);
        l->length--;
    }
    free(l);
}

void left_free(linked_list *l)
{
    elf *head = l->head;
    if (head->previous != NULL)
    {
        fprintf(stderr, "Error: the head does not point at the begining of the linked list.\n");
        exit(EXIT_FAILURE);
    }
    l->head = head->next;
    l->length--;
    free(head);
    if (l->length == 0)
    { // The element has already been free
        l->tail = NULL;
    }
    else
    {
        l->head->previous = NULL;
    }
}

void right_free(linked_list *l)
{
    elf *tail = l->tail;
    if (tail->next != NULL)
    {
        fprintf(stderr, "Error: the tail does not point at the end of the linked list.\n");
        exit(EXIT_FAILURE);
    }
    l->tail = tail->previous;
    l->length--;
    free(tail);
    if (l->length == 0)
    { // The element has already been free
        l->head = NULL;
    }
    else
    {
        l->tail->next = NULL;
    }
}

bool is_empty(linked_list *l)
{
    return l->length == 0;
}

void print_list(linked_list *l)
{

    elf *cursor = l->head;
    int i = 0;
    while (i < l->length)
    {
        printf("%i\n", cursor->calories);
        cursor = cursor->next;
        i++;
    }
}

void prepend(linked_list *l, elf *elf)
{
    if (!is_empty(l))
    {

        elf->next = l->head;
        l->head->previous = elf;
        l->head = elf;
    }
    else
    {
        l->head = elf;
        l->tail = elf;
    }
    l->length++;
    if (l->length > l->length_max)
    {
        right_free(l);
    }
}

void append(linked_list *l, elf *_elf)
{
    if (is_empty(l))
    {
        l->head = _elf;
        l->tail = _elf;
    }
    else if (l->length < l->length_max)
    {
        _elf->previous = l->tail;
        l->tail->next = _elf;
        l->tail = _elf;
        l->length++;
    }
    else
    {
        free(_elf);
    }
}

void insert(linked_list *l, int calories)
{
    elf *_elf = elf_init(calories);
    if (is_empty(l))
    {
        prepend(l, _elf);
        return;
    }
    if (_elf->calories < l->tail->calories)
    {
        append(l, _elf);
        return;
    }
    int i = 0;
    elf *cursor = l->head;
    while (i < l->length)
    {
        if (_elf->calories > cursor->calories)
        {
            if (i == 0)
            {
                prepend(l, _elf);
                break;
            }

            cursor->previous->next = _elf;
            _elf->previous = cursor->previous;
            _elf->next = cursor;
            cursor->previous = _elf;
            l->length++;
            right_free(l);
            break;
        }
        cursor = cursor->next;
        i++;
    }
}