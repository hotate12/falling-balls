#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

void check_win_size()
{
    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    while (max_y < MIN_HEIGHT || max_x < MIN_WIDTH)
    {
        clear();
        mvprintw(0, 0, "画面が小さすぎます");
        mvprintw(1, 0, "画面を大きくしてください");
        refresh();
        usleep(100000);
        getmaxyx(stdscr, max_y, max_x);
    }
}

void init_exit_scr(const int selected)
{
    clear();

    int max_y = 0, max_x = 0, reference_y = 0, reference_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    char *menu[] = {"Yes", "No "};
    char message[] = "本当に終了しますか？";
    const int msg_len = 15;

    reference_y = max_y / 2 - 5;
    reference_x = (max_x - msg_len) / 2 - 4;

    mvprintw(reference_y + 1, (max_x - msg_len / 3) / 2 - 7, "%s", message);

    for (int i = 0; i < 2; i++)
    {
        char item[255];
        if (i == selected)
        {
            snprintf(item, 255, "> %s <", menu[i]);
            attron(COLOR_PAIR(1));
            mvprintw(reference_y + 3 + i, (max_x - strlen(item)) / 2, "%s", item);
            attroff(COLOR_PAIR(1));
        }
        else
        {
            snprintf(item, 255, "  %s  ", menu[i]);
            mvprintw(reference_y + 3 + i, (max_x - strlen(item)) / 2, "%s", item);
        }
    }

    mvhline(reference_y, reference_x, ACS_HLINE, msg_len + 8);
    mvaddch(reference_y, reference_x, ACS_ULCORNER);
    mvaddch(reference_y, reference_x + msg_len + 7, ACS_URCORNER);

    for (int i = 0; i < 4; i++)
    {
        mvaddch(reference_y + 1 + i, reference_x, ACS_VLINE);
        mvaddch(reference_y + 1 + i, reference_x + msg_len + 7, ACS_VLINE);
    }

    mvhline(reference_y + 5, reference_x, ACS_HLINE, msg_len + 8);
    mvaddch(reference_y + 5, reference_x, ACS_LLCORNER);
    mvaddch(reference_y + 5, reference_x + msg_len + 7, ACS_LRCORNER);

    refresh();
}

int exit_scr()
{
    int selected = 0;
    int input_key = 0;
    bool flag = false;

    do
    {
        init_exit_scr(selected);
        input_key = getch();
        switch (input_key)
        {
        case KEY_UP:
            if (selected > 0)
                selected--;
            break;
        case KEY_DOWN:
            if (selected < 1)
                selected++;
            break;
        case '\n':
            if (selected == 0)
            {
                return 1;
            }
            else
            {
                flag = true;
            }
            break;
        }
    } while (flag == false);

    return 0;
}

void load_game_help()
{
    clear();

    int max_y = 0, max_x = 0, reference_y = 0, reference_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    reference_y = max_y / 2 - 8;
    reference_x = max_x / 2 - 36;

    const int lines = 10;
    char *content[lines];

    read_file(content, lines);

    for (int i = 0; i < lines; i++)
    {
        mvprintw(reference_y + 1 + i, reference_x + 2, "%s", content[i]);
    }
    mvprintw(reference_y + 12, reference_x + 29, "'q' で終了");

    mvhline(reference_y, reference_x, ACS_HLINE, 70);
    mvaddch(reference_y, reference_x, ACS_ULCORNER);
    mvaddch(reference_y, reference_x + 69, ACS_URCORNER);

    for (int i = 0; i < 13; i++)
    {
        mvaddch(reference_y + 1 + i, reference_x, ACS_VLINE);
        mvaddch(reference_y + 1 + i, reference_x + 69, ACS_VLINE);
    }

    mvhline(reference_y + 13, reference_x, ACS_HLINE, 70);
    mvaddch(reference_y + 13, reference_x, ACS_LLCORNER);
    mvaddch(reference_y + 13, reference_x + 69, ACS_LRCORNER);

    refresh();

    while (getch() != 'q')
        ;
}

void load_scores()
{
    clear();

    int max_y = 0, max_x = 0, reference_y = 0, reference_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    reference_y = max_y / 2 - 8;
    reference_x = max_x / 2 - 25;

    database ranking_data[3];
    database hist_scores[3];

    read_csv(ranking_data, 0, 3);
    read_csv(hist_scores, 3, 3);

    mvprintw(reference_y + 1, reference_x + 21, "Ranking");
    for (int i = 0; i < 3; i++)
    {
        mvprintw(reference_y + 2 + i, reference_x + 5, "%d. %s", i + 1, ranking_data[i].name);
        mvprintw(reference_y + 2 + i, reference_x + 35, "score: %3d", ranking_data[i].score);
    }

    mvprintw(reference_y + 6, reference_x + 18, "Score history");
    for (int i = 0; i < 3; i++)
    {
        mvprintw(reference_y + 7 + i, reference_x + 5, "%s", hist_scores[i].date);
        mvprintw(reference_y + 7 + i, reference_x + 35, "score: %3d", hist_scores[i].score);
    }

    mvprintw(reference_y + 10, reference_x + 9, "直近３件のスコアのみ表示されます");
    mvprintw(reference_y + 12, reference_x + 20, "'q' で終了");

    mvhline(reference_y, reference_x, ACS_HLINE, 50);
    mvaddch(reference_y, reference_x, ACS_ULCORNER);
    mvaddch(reference_y, reference_x + 49, ACS_URCORNER);

    for (int i = 0; i < 13; i++)
    {
        mvaddch(reference_y + 1 + i, reference_x, ACS_VLINE);
        mvaddch(reference_y + 1 + i, reference_x + 49, ACS_VLINE);
    }

    mvhline(reference_y + 13, reference_x, ACS_HLINE, 50);
    mvaddch(reference_y + 13, reference_x, ACS_LLCORNER);
    mvaddch(reference_y + 13, reference_x + 49, ACS_LRCORNER);

    refresh();

    while (getch() != 'q')
        ;
}
