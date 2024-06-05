/*
** EPITECH PROJECT, 2023
** my_stradd
** File description:
** my_stradd
*/

#include "../../include/my.h"
#include <stdlib.h>

char *my_stradd(char *src, char c)
{
    int len;
    char *str;

    if (c == 0)
        src[0] = '\0';
    for (len = 0; src[len] != '\0'; len++);
    str = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++) {
        str[i] = src[i];
    }
    str[len] = c;
    str[len + 1] = src[len];
    return str;
}
