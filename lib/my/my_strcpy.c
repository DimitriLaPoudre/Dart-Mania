/*
** EPITECH PROJECT, 2023
** my_strcpy
** File description:
** copy a string into another string
*/

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for ( ; dest[i] != '\0' || src[i] != '\0'; i = i + 1){
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
