/*
** EPITECH PROJECT, 2023
** Standard File
** File description:
** my_malloc.c
*/

#include "../../include/garbage.h"

static void add_garbage(garbage_t **list, void *data)
{
    garbage_t *param = malloc(sizeof(*param));
    garbage_t *tmp = *list;

    param->data = data;
    param->next = NULL;
    if (tmp == NULL) {
        *list = param;
    } else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = param;
    }
}

void *allocat(void *(*create)(void *), void *size, void (*destroy)(void *))
{
    static garbage_t *garbage = NULL;
    allocat_t *dstruct = NULL;

    if (size != 0) {
        dstruct = malloc(sizeof(allocat_t));
        dstruct->data_alloc = create(size);
        dstruct->f = destroy;
        add_garbage(&garbage, dstruct);
        return dstruct->data_alloc;
    }
    for (garbage_t *tmp = garbage; garbage != NULL; tmp = garbage) {
        tmp->data->f(tmp->data->data_alloc);
        free(tmp->data);
        garbage = garbage->next;
        free(tmp);
    }
    return NULL;
}

void *alloc_cc(void *size)
{
    int nb = *(int *)size;

    return malloc(sizeof(char) * (nb + 1));
}
