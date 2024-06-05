/*
** EPITECH PROJECT, 2023
** lib/hunter
** File description:
** create_ballon.c
*/

#include "../../include/my.h"

boom_t *create_boom(menu_t *menu)
{
    static boom_t *boom;

    boom = malloc(sizeof(boom_t));
    boom->x = 0;
    boom->y = 0;
    boom->z = 0;
    boom->r = 0;
    boom->g = 0;
    boom->b = 0;
    boom->sprite = ALLOC_SPRITE_P("sprite/boom.png");
    boom->anim = 5;
    boom->clock = ALLOC_CLOCK;
    boom->pop = ALLOC_SOUND("sound/pop.ogg");
    return boom;
}

void reset_boom(boom_t *boom, ballon_t *ballon, menu_t *menu)
{
    boom->x = ballon->x;
    boom->y = ballon->y;
    boom->z = ballon->z;
    boom->r = ballon->r;
    boom->g = ballon->g;
    boom->b = ballon->b;
    boom->anim = 0;
    sfSound_setVolume(boom->pop, menu->v_fx);
    sfSound_play(boom->pop);
    sfClock_restart(boom->clock);
}

static void set_position(sfRenderWindow *window, boom_t *boom)
{
    sfVector2u size = sfRenderWindow_getSize(window);

    sfSprite_setPosition(boom->sprite\
    , (sfVector2f){boom->x * 1920 / (int)size.x\
    , boom->y * 1010 / (int)size.y});
}

void display_boom(sfRenderWindow *window, boom_t *boom)
{
    sfIntRect area = {22 * boom->anim, 0, 16, 40};
    sfVector2f position = {boom->x, boom->y};
    sfVector2f size = {boom->z, boom->z};
    sfColor color = {boom->r, boom->g, boom->b, 255};

    if (boom->anim != 5) {
        set_position(window, boom);
        sfSprite_setScale(boom->sprite, size);
        sfSprite_setColor(boom->sprite, color);
        sfSprite_setTextureRect(boom->sprite, area);
        sfRenderWindow_drawSprite(window, boom->sprite, NULL);
        if (sfTime_asSeconds(\
        sfClock_getElapsedTime(boom->clock)) > 0.08) {
            boom->anim++;
            sfClock_restart(boom->clock);
        }
    }
}
