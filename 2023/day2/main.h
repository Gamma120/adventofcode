#define BUFF_MAX 1024
#define DIGITS "0123456789"
#define INITIAL_DRAW_SIZE 5

typedef struct
{
    int blue;
    int green;
    int red;
} Draw;

typedef struct
{
    int id;
    int draw_count;
    int draw_max;
    Draw *draws;
} Game;

Game *game_create(int id);
void game_destroy(Game *game);
void game_add_draw(Game *game, Draw draw);
void game_fill(Game *game, char *line);

int parse_id(char *line);

int main(int argc, char *argv[]);
