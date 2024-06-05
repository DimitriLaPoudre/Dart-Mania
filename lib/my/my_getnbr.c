/*
** EPITECH PROJECT, 2023
** my_getnbr
** File description:
** my_getbr
*/

#include "../../include/my.h"

long long my_getnbr(char *str)
{
    long long nb = 0;

    for (int i = 0; str[i] >= 48 && str[i] <= 57; i++)
        nb = nb * 10 + str[i] - 48;
    return nb;
}
