/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** strdup man ca vit hein
*/

#include <stddef.h>
#include <stdlib.h>

char *my_strdup(char const *src)
{
    int len;
    char *str;

    if (src == NULL)
        return NULL;
    for (len = 0; src[len] != '\0'; len++);
    str = malloc(sizeof(char) * len + 1);
    if (str == NULL)
        return NULL;
    for (int i = 0; i <= len; i++)
        str[i] = src[i];
    return str;
}
