#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "main.h"

Game *game_create(int id)
{
    Game *game;
    game = malloc((sizeof *game) + INITIAL_DRAW_SIZE * (sizeof *game->draws));
    if (game == NULL)
    {
        fprintf(stderr, "Error while malloc: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    game->id = id;
    game->draw_count = 0;
    game->draw_max = INITIAL_DRAW_SIZE;

    Draw *draws;
    draws = calloc((sizeof *draws), INITIAL_DRAW_SIZE);
    if (draws == NULL)
    {
        fprintf(stderr, "Error while malloc: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    game->draws = draws;

    return game;
}

void game_destroy(Game *game)
{
    free(game->draws);
    free(game);
}

void game_add_draw(Game *game, Draw draw)
{
    if (game->draw_count == game->draw_max)
    {
        game->draws = realloc(game->draws, 2 * game->draw_max * (sizeof *game->draws));
        if (game->draws == NULL)
        {
            fprintf(stderr, "Error while realloc: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        game->draw_max *= 2;
    }

    game->draws[game->draw_count] = draw;
    game->draw_count++;
}

void game_fill(Game *game, char *line)
{

    char *draws_str;
    draws_str = strsep(&line, ";");

    while (draws_str != NULL)
    {
        Draw draw = {0, 0, 0};

        char *pick;
        pick = strsep(&draws_str, ",");

        while (pick != NULL)
        {
            int n_size = strspn(pick + 1, DIGITS);
            char *n_str;
            n_str = calloc(sizeof(char), n_size + 1);
            strncpy(n_str, pick + 1, n_size);
            int n = strtol(n_str, NULL, 10);
            free(n_str);

            char color = pick[n_size + 2];

            if (color == 'b')
            {
                draw.blue = n;
            }
            else if (color == 'r')
            {
                draw.red = n;
            }
            else if (color == 'g')
            {
                draw.green = n;
            }

            pick = strsep(&draws_str, ",");
        }
        game_add_draw(game, draw);
        draws_str = strsep(&line, ";");
    }
}

int parse_id(char *line)
{
    char *start = strpbrk(line, DIGITS);
    int n_size = strspn(start, DIGITS);

    char *str_id = calloc(sizeof(char), n_size + 1);
    strncpy(str_id, start, n_size);

    int id = strtol(str_id, NULL, 10);
    free(str_id);
    return id;
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

    char line[BUFF_MAX];
    int sum = 0;

    Draw rule;
    rule.blue = 14;
    rule.red = 12;
    rule.green = 13;

    while (fgets(line, BUFF_MAX, in_ptr) != NULL)
    {

        Game *game = game_create(parse_id(line));
        char *start_draws = strpbrk(line, ":") + 1;
        game_fill(game, start_draws);

        Draw minimal;
        minimal.blue = game->draws[0].blue;
        minimal.green = game->draws[0].green;
        minimal.red = game->draws[0].red;

        bool validity = true;
        for (int i = 0; i < game->draw_count; i++)
        {
            Draw draw = game->draws[i];

            if ((draw.blue > rule.blue) |
                (draw.green > rule.green) |
                (draw.red > rule.red))
            {
                validity = false;
            }

            minimal.blue = draw.blue > minimal.blue ? draw.blue : minimal.blue;
            minimal.green = draw.green > minimal.green ? draw.green : minimal.green;
            minimal.red = draw.red > minimal.red ? draw.red : minimal.red;
        }

        if (part == 1 && validity)
        {
            sum += game->id;
        }

        else if (part == 2)
        {
            sum += minimal.blue * minimal.green * minimal.red;
        }

        game_destroy(game);
    }

    printf("%d\n", sum);

    fclose(in_ptr);
    return EXIT_SUCCESS;
}