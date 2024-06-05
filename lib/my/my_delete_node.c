/*
** EPITECH PROJECT, 2023
** my delete node
** File description:
** delete node with same data than data ref
*/

#include "../../include/my.h"
#include <stdio.h>
#include <stdlib.h>

int my_delete_node(linked_list_t **begin, void const *data_ref)
{
    linked_list_t *tmp = NULL;
    linked_list_t *act = NULL;

    for (act = *begin; act != NULL; act = act->next) {
        if (my_strcmp(act->data, data_ref) == 0 && act == *begin) {
            *begin = act->next;
            return 0;
        }
        if (act == *begin) {
            tmp = act;
            continue;
        }
        if (my_strcmp(act->data, data_ref) == 0) {
            tmp->next = act->next;
            return 0;
        }
        tmp = tmp->next;
    }
    return 0;
}
