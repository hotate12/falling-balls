#ifndef FALLING_BALLS_H
#define FALLING_BALLS_H

#include "game_result.h"

#define GAME_HEIGHT 14
#define GAME_WIDTH 22
#define PLAY_AREA_GAME_HEIGHT 12
#define PLAY_AREA_GAME_WIDTH 20
#define BASKET_LEFT '|'
#define BASKET_CENTER '_'
#define BASKET_RIGHT '|'
#define NORMAL_BALL 'o'
#define SPECIAL_BALL '*'
#define BALL_SPEED 400
#define MAX_BALLS_NUM 10000
#define BOX_GAME_HEIGHT 5
#define BOX_GAME_WIDTH 14

typedef struct
{
    int x;
    int y;
    int next_drop_timing;
    bool active;
    bool flag;
    bool special_ball;
} Ball;

void init_game();
void play_game();
void init_game_screen();
void draw();
Ball random_ball_setting();
void fever_control();
void remaining_time_add(double);
long get_milliseconds();

#endif