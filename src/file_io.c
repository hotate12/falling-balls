#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

void read_file(char *content[], const int max_line)
{
    FILE *file = fopen("./data/help.txt", "r");

    if (file == NULL)
    {
        return;
    }

    char tmp[256];
    int i = 0;

    while (fgets(tmp, sizeof(tmp), file) && i < max_line)
    {
        content[i] = malloc(strlen(tmp) + 1);
        strcpy(content[i], tmp);
        i++;
    }

    fclose(file);
}

void read_csv(database *data, const int start, const int num)
{
    FILE *file = fopen("./data/hist_scores.csv", "r");

    if (file == NULL)
    {
        return;
    }

    char tmp[256];
    int current = 0;

    while (fgets(tmp, sizeof(tmp), file))
    {
        if (current >= start && current < (start + num))
        {
            sscanf(tmp, "%[^,],%d,%[^\n]", data[current - start].date, &data[current - start].score, data[current - start].name);
        }
        current++;
    }

    fclose(file);
}

void write_csv(database *ranking_data, database *hist_scores)
{
    FILE *file = fopen("./data/hist_scores.csv", "w");

    if (file == NULL)
    {
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        fprintf(file, "%s,%d,%s\n", ranking_data[i].date, ranking_data[i].score, ranking_data[i].name);
    }

    for (int i = 0; i < 3; i++)
    {
        fprintf(file, "%s,%d,%s\n", hist_scores[i].date, hist_scores[i].score, hist_scores[i].name);
    }

    fclose(file);
}
