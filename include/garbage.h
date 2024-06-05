/*
** EPITECH PROJECT, 2023
** Standard File
** File description:
** garbage.h
*/

#ifndef GARBAGE
    #define GARBAGE

    #define ALLOC_CC(len) allocat(&alloc_cc, &len, &free)
    #define ALLOC_SPRITE_P(p) ((s_t *)allocat(&asprite, p, &dsprite))->sprite
    #define ALLOC_SOUND(p) ((sound_t *)allocat(&asound, p, &dsound))->sound
    #define ALLOC_CLOCK ((sfClock *)allocat(&alloc_clock, "-1", &dalloc_clock))
    #define DALLOC allocat(NULL, 0, NULL)

    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>

typedef struct allocation {
    void *data_alloc;
    void (*f)(void *);
} allocat_t;

typedef struct garbage {
    allocat_t *data;
    struct garbage *next;
} garbage_t;

typedef struct sprite {
    sfTexture *texture;
    sfSprite *sprite;
} s_t;

typedef struct sound {
    sfSoundBuffer *sb;
    sfSound *sound;
} sound_t;

void *allocat(void *(*create)(void *), void *size, void (*destroy)(void *));

void *alloc_cc(void *size);

void *asprite(void *path);

void dsprite(void *base);

void *asound(void *path);

void dsound(void *base);

void *alloc_clock(void *path);

void dalloc_clock(void *base);

#endif
