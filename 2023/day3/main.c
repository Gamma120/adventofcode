#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "main.h"

bool is_digit(char c)
{
    return c - '0' < 10 && c - '0' >= 0;
}

void overwrite(char *line, int begin, int end)
{
    for (int i = begin; i <= end; i++)
    {
        line[i] = '.';
    }
}

int get_number(char *line, int position)
{
    if (line == NULL)
    {
        return 0;
    }

    if (!is_digit(line[position]))
    {
        // there is no number here
        return 0;
    }

    int left = position - 1;
    if (left >= 0 && is_digit(line[left]))
    {
        // the number does not begin at position
        return 0;
    }

    int n_length = strspn(line + position, DIGITS);
    char *n_str = calloc(sizeof(char), n_length + 1);
    n_str = strncpy(n_str, line + position, n_length);
    int number = strtol(n_str, NULL, 10);
    free(n_str);

    // erase the number to not count it multiple times
    overwrite(line, position, position + n_length - 1);

    return number;
}

int get_right_number(char *line, int symbol_position)
{
    return get_number(line, symbol_position + 1);
}

int get_center_number(char *line, int symbol_position)
{
    return get_number(line, symbol_position);
}

int get_left_number(char *line, int symbol_position)
{
    if (line == NULL)
    {
        return 0;
    }

    int cursor = symbol_position - 1;
    while (cursor >= 0 && is_digit(line[cursor]))
    {
        cursor--;
    }

    int number_begin = cursor + 1;

    return get_number(line, number_begin);
}

int main(int argc, char *argv[])
{
    /*
    argv[1]: input file
    argv[2]: problem part
    */
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <file> <part>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *in_path = argv[1];
    FILE *in_ptr = fopen(in_path, "r");

    int part = strtol(argv[2], NULL, 10);
    if (part != 1 && part != 2)
    {
        fprintf(stderr, "Error: part value must be 1 or 2\n");
        exit(EXIT_FAILURE);
    }

    if (in_ptr == NULL)
    {
        fprintf(stderr, "Error while opening %s: %s\n", in_path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char *previous, *current, *next;
    previous = malloc((sizeof *previous) * BUFF_MAX);
    current = malloc((sizeof *current) * BUFF_MAX);
    next = malloc((sizeof *next) * BUFF_MAX);

    // save the pointers to free it at the end
    char *save_previous, *save_current, *save_next;
    save_previous = previous;
    save_current = current;
    save_next = next;

    fgets(previous, BUFF_MAX, in_ptr);
    fgets(current, BUFF_MAX, in_ptr);
    fgets(next, BUFF_MAX, in_ptr);

    int sum = 0;
    int length = strnlen(previous, BUFF_MAX);
    while (current != NULL)
    {
        char *lines[3] = {previous, current, next};
        Func func[3] = {&get_left_number,
                        &get_center_number,
                        &get_right_number};

        int cursor = strspn(current, NOT_SYMBOLS);
        while (cursor < length - 1)
        {
            if (part == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        sum += func[j](lines[i], cursor);
                    }
                }
            }

            else if (part == 2 && current[cursor] == '*')
            {
                int count = 0;
                int mul = 1;

                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        int val = func[j](lines[i], cursor);
                        if (val > 0)
                        {
                            mul *= val;
                            count++;
                        }
                    }
                }

                if (count == 2)
                {
                    sum += mul;
                }
            }

            cursor++;
            cursor += strspn(current + cursor, NOT_SYMBOLS);
        }

        char *tmp = previous;
        previous = current;
        current = next;
        next = fgets(tmp, BUFF_MAX, in_ptr);
    }

    printf("%d\n", sum);

    free(save_previous);
    free(save_current);
    free(save_next);
    fclose(in_ptr);

    return EXIT_SUCCESS;
}