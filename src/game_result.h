#ifndef GAME_RESULT_H
#define GAME_RESULT_H

#include "file_io.h"

#define GAME_HEIGHT 14
#define GAME_WIDTH 22

void result(const int);
void save_score(const int);
void update_csv(int, char[]);
void input_user_name(char *);

#endif