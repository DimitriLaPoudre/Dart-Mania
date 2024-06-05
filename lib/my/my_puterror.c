/*
** EPITECH PROJECT, 2023
** my_putstr
** File description:
** my_putstr
*/

#include "../../include/my.h"
#include <unistd.h>

void my_puterror(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        write(2, &str[i], 1);
}
