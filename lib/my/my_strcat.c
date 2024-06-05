/*
** EPITECH PROJECT, 2023
** my_strcat
** File description:
** yes la fonction tsé
*/

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int test = 0;

    for (; dest[i] != '\0'; i++);
    for (; src[test] != '\0'; test++) {
        dest[i + test] = src[test];
    }
    dest[i + test] = '\0';
    return dest;
}
