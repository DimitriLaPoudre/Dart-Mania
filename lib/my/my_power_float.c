/*
** EPITECH PROJECT, 2023
** my_power_float
** File description:
** my_power_float
*/

#include "../../include/my.h"

long double my_power_float(long double nb, int p)
{
    long double result = nb;

    if (p == 0) {
        return (1);
    }else if (p < 0) {
        return (0);
    }
    result = nb * my_power_float(nb, p - 1);
    return (result);
}
