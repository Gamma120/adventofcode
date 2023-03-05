#pragma once

#include "elf.h"

void update_rank(elf **list_begin, elf **list_end, elf *current_elf);
void init_rank(elf **list_begin, elf **list_end, elf *current_elf);
int main(int argc, char *argv[]);
