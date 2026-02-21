#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main()
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);

    start_scr();

    endwin();

    return 0;
}

void init_start_scr(const int selected)
{
    clear();

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    int max_y = 0, max_x = 0, reference_y = 0, reference_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    char *menu[] = {"Play", "Scores", "Help", "Exit"};
    char game_title[] = "Falling Balls";

    int title_len = strlen(game_title);
    for (int i = 0; i < 4; i++)
    {
        if (strlen(menu[i]) > title_len)
        {
            title_len = strlen(menu[i]);
        }
    }

    reference_y = max_y / 2 - 7;
    reference_x = (max_x - title_len) / 2 - 4;

    mvprintw(reference_y + 1, (max_x - title_len) / 2, "%s", game_title);

    for (int i = 0; i < 4; i++)
    {
        char item[256];
        if (i == selected)
        {
            snprintf(item, 255, "> %s <", menu[i]);
            attron(COLOR_PAIR(1));
            mvprintw(reference_y + 4 + i, (max_x - strlen(item)) / 2, "%s", item);
            attroff(COLOR_PAIR(1));
        }
        else
        {
            snprintf(item, 255, "  %s  ", menu[i]);
            mvprintw(reference_y + 4 + i, (max_x - strlen(item)) / 2, "%s", item);
        }
    }

    mvhline(reference_y, reference_x, ACS_HLINE, title_len + 8);
    mvaddch(reference_y, reference_x, ACS_ULCORNER);
    mvaddch(reference_y, reference_x + title_len + 7, ACS_URCORNER);

    for (int i = 0; i < 9; i++)
    {
        mvaddch(reference_y + 1 + i, reference_x, ACS_VLINE);
        mvaddch(reference_y + 1 + i, reference_x + title_len + 7, ACS_VLINE);
    }

    mvhline(reference_y + 9, reference_x, ACS_HLINE, title_len + 8);
    mvaddch(reference_y + 9, reference_x, ACS_LLCORNER);
    mvaddch(reference_y + 9, reference_x + title_len + 7, ACS_LRCORNER);

    refresh();
}

void start_scr()
{
    int selected = 0;
    int input_key;

    do
    {
        check_win_size();

        init_start_scr(selected);
        input_key = getch();

        switch (input_key)
        {
        case KEY_UP:
            if (selected > 0)
                selected--;
            break;
        case KEY_DOWN:
            if (selected < 3)
                selected++;
            break;
        case '\n':
            switch (selected)
            {
            case 0:
                play_game();
                break;
            case 1:
                load_scores();
                break;
            case 2:
                load_game_help();
                break;
            case 3:
                if (exit_scr() == 1)
                {
                    endwin();
                    exit(0);
                }
                selected = 0;
                break;
            }
        }
    } while (true);
}
