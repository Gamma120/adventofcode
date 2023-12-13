#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "main.h"

#define BUFF_MAX 100

char *digits[10] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"};

bool is_digit(char c)
{
    return c - '0' < 10 && c - '0' > 0;
}

int is_letters_digit(char *c)
{
    int length = strlen(c);

    if (length < 3)
    {
        return 0;
    }

    for (int i = 1; i < 10; i++)
    {
        if (strncmp(c, digits[i], strlen(digits[i])) == 0)
        {
            return i;
        }
    }

    return 0;
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

    int part = atoi(argv[2]);
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

    char line[BUFF_MAX];
    int numbers[BUFF_MAX];
    int sum = 0;

    while (fgets(line, BUFF_MAX, in_ptr) != NULL)
    {
        int l = 0;
        int n = 0;
        while (l < BUFF_MAX && line[l] != '\n')
        {
            int d;
            if (is_digit(line[l]))
            {
                numbers[n] = line[l] - '0';
                n++;
            }
            else if (part == 2 && (d = is_letters_digit(&line[l])) != 0)
            {
                numbers[n] = d;
                n++;
            }

            l++;
        }

        if (n > 0)
        {
            int calibration = numbers[0] * 10 + numbers[n - 1];
            sum += calibration;
        }
    }

    printf("%d\n", sum);

    fclose(in_ptr);
    return EXIT_SUCCESS;
}