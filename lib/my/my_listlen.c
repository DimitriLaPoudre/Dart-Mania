/*
** EPITECH PROJECT, 2023
** my_listlen.c
** File description:
** my_listlen.c
*/

#include "../../include/linked_list.h"
#include <stdlib.h>

int my_listlen(linked_list_t *begin)
{
    int i = 0;
    linked_list_t *tmp;

    tmp = begin;
    for (; tmp != NULL; i++)
        tmp = tmp->next;
    return i;
}
