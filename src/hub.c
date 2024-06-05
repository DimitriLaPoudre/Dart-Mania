/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** hub.c
*/

#include "../include/my.h"

int main(int ac, char **av)
{
    if (ac == 2 && !my_strcmp(av[1], "-h")) {
        help();
        return 0;
    } else if (ac == 1) {
        menu();
        return 0;
    }
    return 84;
}
