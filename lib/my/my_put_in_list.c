/*
** EPITECH PROJECT, 2023
** my_put_in_list.c
** File description:
** my_put_in_list.c
*/

#include "../../include/linked_list.h"
#include <stdlib.h>

void my_put_in_list(linked_list_t **list, char *data)
{
    linked_list_t *param;

    param = malloc(sizeof(*param));
    param->data = data;
    param->next = *list;
    *list = param;
}
