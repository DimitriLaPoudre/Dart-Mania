/*
** EPITECH PROJECT, 2023
** my_rev_list.c
** File description:
** my_rev_list.c
*/

#include "../../include/linked_list.h"
#include "../../include/my.h"
#include <stdlib.h>

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *tmp_a = NULL;
    linked_list_t *tmp_b = NULL;
    linked_list_t *beginning = NULL;
    int len = 0;

    len = my_listlen(*begin);
    beginning = *begin;
    tmp_a = beginning;
    tmp_b = beginning;
    for (; tmp_a->next != NULL; tmp_a = tmp_a->next)
        ;
    *begin = tmp_a;
    for (int j = 0; j <= len; j++) {
        for (int i = 0; tmp_b->next != tmp_a; tmp_b = tmp_b->next)
            ;
        tmp_a->next = tmp_b;
        tmp_a = tmp_b;
        tmp_b = beginning;
    }
    tmp_a->next = NULL;
}
