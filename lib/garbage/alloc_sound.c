/*
** EPITECH PROJECT, 2023
** Standard File
** File description:
** my_malloc.c
*/

#include "../../include/garbage.h"

void *asound(void *path)
{
    sound_t *base = malloc(sizeof(sound_t));

    base->sb = sfSoundBuffer_createFromFile((char *)path);
    base->sound = sfSound_create();
    sfSound_setBuffer(base->sound, base->sb);
    return (void *)base;
}

void dsound(void *base)
{
    sfSoundBuffer_destroy(((sound_t *)base)->sb);
    sfSound_destroy(((sound_t *)base)->sound);
    free(base);
}
