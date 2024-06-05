/*
** EPITECH PROJECT, 2023
** my_strcmp
** File description:
** yes man sale fpd de marvin
*/

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    for (; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++);
    if (s1[i] == '\0' && s2[i] == '\0')
        return 0;
    else if (s1[i] < s2[i])
        return s1[i] - s2[i];
    else
        return s1[i] - s2[i];
}
