/*
** EPITECH PROJECT, 2023
** my_putnbr_base
** File description:
** my_putnbr_base
*/

#include "../../include/my.h"

void my_putnbr_base(unsigned long long nb, char const *base)
{
    int t_base = 0;

    t_base = my_strlen(base);
    if (nb >= t_base)
        my_putnbr_base(nb / t_base, base);
    my_putchar(base[nb % t_base]);
}
