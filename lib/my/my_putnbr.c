/*
** EPITECH PROJECT, 2023
** my_putnbr
** File description:
** my_putnbr
*/

#include "../../include/my.h"

void my_putnbr(long long nb)
{
    int n = 0;

    if (nb < 0) {
        my_putchar('-');
        nb = -nb - 1;
        n = 1;
    }
    if (nb >= 10)
        my_putnbr(nb / 10);
    my_putchar(nb % 10 + 48 + n);
}
