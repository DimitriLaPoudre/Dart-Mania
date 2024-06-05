/*
** EPITECH PROJECT, 2023
** Standard File
** File description:
** my_malloc.c
*/

#include "../../include/garbage.h"

void *alloc_clock(void *path)
{
    return (void *)sfClock_create();
}

void dalloc_clock(void *base)
{
    sfClock_destroy((sfClock *)base);
}
