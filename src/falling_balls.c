#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#include "falling_balls.h"

int x = PLAY_AREA_GAME_WIDTH / 2;
int y = PLAY_AREA_GAME_HEIGHT - 1;
int score = 0;
double game_time = 30;
double fever_time_remaining = 8;
int catch_count = 0;
bool fever_active = false;
bool five_seconds_flag = false;

Ball balls[MAX_BALLS_NUM];

void init_game()
{
    x = PLAY_AREA_GAME_WIDTH / 2;
    y = PLAY_AREA_GAME_HEIGHT - 1;
    score = 0;
    game_time = 30;
    fever_time_remaining = 8;
    catch_count = 0;
    fever_active = false;
    five_seconds_flag = false;

    for (int i = 0; i < MAX_BALLS_NUM; i++)
    {
        balls[i] = random_ball_setting();
    }
}

void play_game()
{
    init_game();

    srand(time(0));

    long start_time = get_milliseconds();
    long prev_time_ball_drop = start_time;

    balls[0].active = true;

    nodelay(stdscr, TRUE);

    while (game_time > 0)
    {
        int ch = getch();
        if (ch == 'q')
        {
            nodelay(stdscr, FALSE);
            if (exit_scr() == 1)
            {
                break;
            }
            nodelay(stdscr, TRUE);
        }

        if (ch != ERR && ch != KEY_LEFT && ch != KEY_RIGHT)
        {
            continue;
        }

        if (ch == KEY_LEFT && x > 1)
        {
            x--;
            draw();
        }
        else if (ch == KEY_RIGHT && x < PLAY_AREA_GAME_WIDTH)
        {
            x++;
            draw();
        }

        long curr_time = get_milliseconds();

        if (curr_time - prev_time_ball_drop >= BALL_SPEED)
        {
            for (int i = 0; i < MAX_BALLS_NUM; i++)
            {
                if (balls[i].active == true)
                {
                    balls[i].y++;

                    if (balls[i].y == y && (balls[i].x > x - 1 && balls[i].x < x + 1))
                    {
                        catch_count++;

                        if (catch_count >= 8)
                        {
                            fever_active = true;
                            fever_time_remaining = 8;
                            catch_count = 0;
                            remaining_time_add(5);
                        }
                        if (balls[i].special_ball == false)
                        {
                            if (fever_active == true)
                            {
                                score += 2;
                                remaining_time_add(1.6);
                            }
                            else
                            {
                                score += 1;
                                remaining_time_add(0.8);
                            }
                        }
                        else
                        {
                            if (fever_active == true)
                            {
                                score += 6;
                                remaining_time_add(4);
                            }
                            else
                            {
                                score += 3;
                                remaining_time_add(2);
                            }
                        }

                        balls[i].active = false;
                    }

                    else if (balls[i].y > PLAY_AREA_GAME_HEIGHT)
                    {
                        if (fever_active == false)
                        {
                            remaining_time_add(-1);
                        }

                        balls[i].active = false;
                        catch_count = 0;
                    }
                }
                else if (i > 0 && balls[i - 1].y >= balls[i].next_drop_timing && balls[i].flag == false)
                {
                    balls[i].active = true;
                    balls[i].flag = true;
                }
            }

            prev_time_ball_drop = curr_time;
            draw();
        }

        if (curr_time - start_time >= 1000)
        {
            start_time = curr_time;
            game_time--;
            fever_control();

            if (game_time <= 5)
            {
                five_seconds_flag = true;
            }
            else
            {
                five_seconds_flag = false;
            }
            draw();
        }
    }

    nodelay(stdscr, FALSE);
    result(score);
    save_score(score);
}

void init_game_screen()
{
    int max_y = 0, max_x = 0, reference_y = 0, reference_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    reference_y = (max_y - GAME_HEIGHT) / 2;
    reference_x = (max_x - GAME_WIDTH) / 2 - 10;

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    if (fever_active == true)
    {
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
    }

    if (five_seconds_flag == true)
    {
        init_pair(1, COLOR_RED, COLOR_BLACK);
    }

    attron(COLOR_PAIR(1));

    for (int i = 0; i < GAME_HEIGHT; i++)
    {
        for (int j = 0; j < GAME_WIDTH; j++)
        {
            if (i == 0 && j == 0)
            {
                mvaddch(i + reference_y, j + reference_x, ACS_ULCORNER);
            }
            else if (i == 0 && j == GAME_WIDTH - 1)
            {
                mvaddch(i + reference_y, j + reference_x, ACS_URCORNER);
            }
            else if (i == GAME_HEIGHT - 1 && j == 0)
            {
                mvaddch(i + reference_y, j + reference_x, ACS_LLCORNER);
            }
            else if (i == GAME_HEIGHT - 1 && j == GAME_WIDTH - 1)
            {
                mvaddch(i + reference_y, j + reference_x, ACS_LRCORNER);
            }
            else if (i == 0 || i == GAME_HEIGHT - 1)
            {
                mvaddch(i + reference_y, j + reference_x, ACS_HLINE);
            }
            else if (j == 0 || j == GAME_WIDTH - 1)
            {
                mvaddch(i + reference_y, j + reference_x, ACS_VLINE);
            }
        }
    }

    attroff(COLOR_PAIR(1));

    int box_y = 0;
    int box_x = 0;
    for (int i = 0; i < BOX_GAME_HEIGHT; i++)
    {
        for (int j = 0; j < BOX_GAME_WIDTH; j++)
        {
            box_y = reference_y + i;
            box_x = (max_x - GAME_WIDTH) / 2 + 20 + j;

            if (i == 0 && j == 0)
            {
                mvaddch(box_y, box_x, ACS_ULCORNER);
            }
            else if (i == 0 && j == BOX_GAME_WIDTH - 1)
            {
                mvaddch(box_y, box_x, ACS_URCORNER);
            }
            else if (i == BOX_GAME_HEIGHT - 1 && j == 0)
            {
                mvaddch(box_y, box_x, ACS_LLCORNER);
            }
            else if (i == BOX_GAME_HEIGHT - 1 && j == BOX_GAME_WIDTH - 1)
            {
                mvaddch(box_y, box_x, ACS_LRCORNER);
            }
            else if (i == 0 || i == BOX_GAME_HEIGHT - 1)
            {
                mvaddch(box_y, box_x, ACS_HLINE);
            }
        }
    }
}

void draw()
{
    clear();

    init_game_screen();

    int max_y = 0, max_x = 0, reference_y = 0, reference_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    reference_y = (max_y - GAME_HEIGHT) / 2;
    reference_x = (max_x - GAME_WIDTH) / 2 - 10;

    mvaddch(y + reference_y, x - 1 + reference_x, BASKET_LEFT);
    mvaddch(y + reference_y, x + reference_x, BASKET_CENTER);
    mvaddch(y + reference_y, x + 1 + reference_x, BASKET_RIGHT);

    for (int i = 0; i < MAX_BALLS_NUM; i++)
    {
        if (balls[i].active == true)
        {
            if (balls[i].special_ball == false)
            {
                mvprintw(balls[i].y + reference_y, balls[i].x + reference_x, "%c", NORMAL_BALL);
            }
            else
            {
                mvprintw(balls[i].y + reference_y, balls[i].x + reference_x, "%c", SPECIAL_BALL);
            }
        }
    }

    int fever_bar_y = 0, fever_bar_x = 0;
    fever_bar_y = reference_y + PLAY_AREA_GAME_HEIGHT + 2;
    fever_bar_x = reference_x + 2;

    mvprintw(fever_bar_y, fever_bar_x, "|");
    for (int i = 1; i <= 8; i++)
    {
        if ((fever_active == true && i <= fever_time_remaining) || (fever_active == false && i <= catch_count))
        {
            mvprintw(fever_bar_y, fever_bar_x + i * 2 - 1, "==");
        }
        else
        {
            mvprintw(fever_bar_y, fever_bar_x + i * 2, "  ");
        }
    }
    mvprintw(fever_bar_y, fever_bar_x + 17, "|");

    mvprintw(reference_y + 1, (max_x - GAME_WIDTH) / 2 + 20, "  Score: %3d  ", score);
    mvprintw(reference_y + 2, (max_x - GAME_WIDTH) / 2 + 20, "  Time : %3.0lf  ", game_time);
    mvprintw(reference_y + 3, (max_x - GAME_WIDTH) / 2 + 21, " 'q' で終了 ");

    refresh();
}

Ball random_ball_setting()
{
    Ball ball;
    ball.x = (rand() % (PLAY_AREA_GAME_WIDTH - 2)) + 1;
    ball.y = 1;
    ball.next_drop_timing = rand() % 4 + 4;
    ball.active = false;
    ball.flag = false;

    int random_num = rand() % 5 + 1;
    if (random_num == 1)
    {
        ball.special_ball = true;
    }
    else
    {
        ball.special_ball = false;
    }

    return ball;
}

void fever_control()
{
    if (fever_active == true)
    {
        fever_time_remaining--;
        catch_count = 0;

        if (fever_time_remaining < 0)
        {
            fever_active = false;
            fever_time_remaining = 8;
        }
    }
}

void remaining_time_add(double add_time)
{
    game_time += add_time;
}

long get_milliseconds()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e3 + currentTime.tv_usec / 1e3;
}
