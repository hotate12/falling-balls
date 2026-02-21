#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game_result.h"

void result(const int score)
{
    clear();

    int max_y = 0, max_x = 0, result_y = 0, result_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    result_y = (max_y - GAME_HEIGHT) / 2 + 5;
    result_x = (max_x - GAME_WIDTH) / 2 + 5;

    mvprintw(result_y, result_x, "Game Over!!\n");
    mvprintw(result_y + 1, result_x, "Your Score: %3d\n", score);

    refresh();

    sleep(2);
}

void save_score(const int score)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char date[24];
    sprintf(date, "%02d-%02d %02d:%02d:%02d", tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    update_csv(score, date);
}

void update_csv(int score, char date[])
{
    database ranking_data[3] = {{"No data", 0, "No data"}, {"No data", 0, "No data"}, {"No data", 0, "No data"}};
    database hist_scores[3] = {{"No data", 0, "No data"}, {"No data", 0, "No data"}, {"No data", 0, "No data"}};

    read_csv(ranking_data, 0, 3);
    read_csv(hist_scores, 3, 3);

    for (int i = 2; i > 0; --i)
    {
        hist_scores[i] = hist_scores[i - 1];
    }
    hist_scores[0].score = score;
    strcpy(hist_scores[0].date, date);

    for (int i = 0; i < 3; ++i)
    {
        if (score > ranking_data[i].score)
        {
            if (score == 0)
            {
                break;
            }
            for (int j = 2; j > i; --j)
            {
                ranking_data[j] = ranking_data[j - 1];
            }
            strcpy(ranking_data[i].date, date);
            ranking_data[i].score = score;
            input_user_name(ranking_data[i].name);
            break;
        }
    }

    write_csv(ranking_data, hist_scores);
}

void input_user_name(char *name)
{
    memset(name, 0, 32);

    int max_y = 0, max_x = 0, reference_y = 0, reference_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    reference_y = max_y / 2 - 6;
    reference_x = max_x / 2 - 20;

    char message1[] = {"congratulation!!"};
    char message2[] = {"ランキングが更新されました"};
    char message3[] = {"名前を入力して Enter を押してください"};

    int input_len = 0;
    int ch = 0;

    echo();

    while (1)
    {
        clear();

        mvhline(reference_y, reference_x, ACS_HLINE, 40);
        mvaddch(reference_y, reference_x, ACS_ULCORNER);
        mvaddch(reference_y, reference_x + 40, ACS_URCORNER);

        for (int i = 0; i < 7; i++)
        {
            mvaddch(reference_y + 1 + i, reference_x, ACS_VLINE);
            mvaddch(reference_y + 1 + i, reference_x + 40, ACS_VLINE);
        }

        mvhline(reference_y + 7, reference_x, ACS_HLINE, 40);
        mvaddch(reference_y + 7, reference_x, ACS_LLCORNER);
        mvaddch(reference_y + 7, reference_x + 40, ACS_LRCORNER);

        mvprintw(reference_y + 1, reference_x + 12, "%s", message1);
        mvprintw(reference_y + 2, reference_x + 7, "%s", message2);
        mvprintw(reference_y + 3, reference_x + 2, "%s", message3);

        mvprintw(reference_y + 5, reference_x + 4, "[");
        mvprintw(reference_y + 5, reference_x + 35, "]");
        mvprintw(reference_y + 5, reference_x + 6, "%s", name);

        refresh();

        ch = getch();

        if (ch == '\n')
            break;
        else if (ch == KEY_BACKSPACE)
        {
            if (input_len > 0)
            {
                input_len--;
                name[input_len] = '\0';
            }
        }
        else if (input_len < 28)
        {
            name[input_len] = ch;
            input_len++;
        }
    }

    noecho();
}
