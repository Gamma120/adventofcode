#define BUFF_MAX 1024
#define DIGITS "0123456789"
#define NOT_SYMBOLS ".0123456789\n"

typedef int (*Func)(char *, int);

int main(int argc, char *argv[]);

int get_number(char *line, int position);
int get_right_number(char *line, int symbol_position);
int get_center_number(char *line, int symbol_position);
int get_left_number(char *line, int symbol_position);

bool is_digit(char c);
void overwrite(char *line, int begin, int end);
