/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** destroyer.c
*/

#include "../../include/my.h"

void destroyer(sfRenderWindow *window, sfClock *clock, sfMusic *music)
{
    sfRenderWindow_destroy(window);
    sfClock_destroy(clock);
    sfMusic_destroy(music);
    DALLOC;
}
