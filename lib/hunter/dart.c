/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** dart.c
*/

#include "../../include/my.h"

dart_t *create_dart(menu_t *menu)
{
    dart_t *dart = malloc(sizeof(dart_t));

    dart->x = 960;
    dart->y = 1030;
    dart->z = 9;
    dart->anim = 0;
    dart->sprite = ALLOC_SPRITE_P("sprite/dart_ss.png");
    sfSprite_setOrigin(dart->sprite, (sfVector2f){4, 30});
    dart->state = 0;
    dart->dist = 0;
    dart->mdist = 0;
    dart->angle = 0;
    dart->clockmove = ALLOC_CLOCK;
    dart->sound = ALLOC_SOUND("sound/swosh.ogg");
    dart->hit = 0;
    return dart;
}

void reset_dart(menu_t *menu, dart_t *dart)
{
    dart->x = 960;
    dart->y = 1030;
    dart->z = 9;
    dart->anim = 0;
    sfSprite_setOrigin(dart->sprite, (sfVector2f){4, 30});
    dart->state = 0;
    dart->dist = 0;
    dart->mdist = 0;
    dart->angle = 0;
    dart->hit = 0;
}

static void missed(menu_t *menu)
{
    static sfSound *missed = NULL;

    if (missed == NULL)
        missed = ALLOC_SOUND("sound/a cote.ogg");
    sfSound_setVolume(missed, menu->v_fx);
    sfSound_play(missed);
}

static void check_ballon(menu_t *menu, all_b_t *b, sfVector2u s, dart_t *dart)
{
    if (b->ballon->x < dart->x * (float)s.x / 1920
    && b->ballon->x + (16 * b->ballon->z)\
    * (float)s.x / 1920 > dart->x * (float)s.x / 1920
    && b->ballon->y < dart->y * (float)s.y / 1010
    && b->ballon->y + (19 * b->ballon->z)\
    * (float)s.y / 1010 > dart->y *(float)s.y / 1010) {
        reset_boom(b->boom, b->ballon, menu);
        reset_ballon(b->ballon, sfRenderWindow_getSize(menu->window));
        b->ballon->s->score++;
        if (b->ballon->s->score > b->ballon->s->record)
            b->ballon->s->record++;
        dart->hit = 1;
    }
}

static void land_dart(menu_t *menu, dart_t *d)
{
    float timem = sfTime_asSeconds(sfClock_getElapsedTime(d->clockmove));

    sfSprite_setOrigin(d->sprite, (sfVector2f){4, 0});
    d->anim += ((float)(d->mdist / d->dist) >= 0.2 * (d->anim + 1)) ? 1 : 0;
    if (timem > 0.0005 && d->mdist + timem * 2000 > d->dist) {
        d->y -= (d->dist - d->mdist) * cos(d->angle * M_PI / 180);
        d->x += (d->dist - d->mdist) * sin(d->angle * M_PI / 180);
        d->z -= (d->dist - d->mdist) / d->dist;
        d->anim = 5;
        return;
    }
    if (timem > 0.0005) {
        d->y -= timem * 2000 * cos(d->angle * M_PI / 180);
        d->x += timem * 2000 * sin(d->angle * M_PI / 180);
        d->mdist += timem * 2000;
        d->z -= 1.8 * timem * 2000 / d->dist;
        sfClock_restart(d->clockmove);
    }
}

static void move_dart(menu_t *menu, dart_t *d, all_b_t *b)
{
    float timem = sfTime_asSeconds(sfClock_getElapsedTime(d->clockmove));

    if (timem > 0.01) {
        if (d->z > b->ballon->z && d->z - 0.1 * timem * 100 <= b->ballon->z)
            check_ballon(menu, b, menu->size, d);
        d->z -= 0.1 * timem * 100;
        sfClock_restart(d->clockmove);
    }
    sfSprite_setOrigin(d->sprite, (sfVector2f){4, 4});
    if (d->z < 3) {
        if (d->hit == 0)
            missed(menu);
        reset_dart(menu, d);
    }
}

void display_order(menu_t *menu, dart_t *dart, all_b_t *b)
{
    display_boom(menu->window, b->boom);
    if (b->ballon->z <= dart->z) {
        display_ballon(menu->window, b->ballon);
        sfRenderWindow_drawSprite(menu->window, dart->sprite, NULL);
    } else {
        sfRenderWindow_drawSprite(menu->window, dart->sprite, NULL);
        display_ballon(menu->window, b->ballon);
    }
}

void display_dart(menu_t *menu, dart_t *dart, all_b_t *b)
{
    sfVector2f dest = {0, 0};

    if (dart->state)
        if (dart->anim < 5)
            land_dart(menu, dart);
        else
            move_dart(menu, dart, b);
    else {
        get_position(&dest.x, &dest.y, menu->window);
        dart->angle = atan2(abs(960.0 - dest.x), abs(1030 - dest.y)) \
        * (180.0 / M_PI);
        if (960.0 - dest.x > 0)
            dart->angle = -(dart->angle);
        sfSprite_setRotation(dart->sprite, dart->angle);
    }
    sfSprite_setTextureRect(dart->sprite, (sfIntRect){dart->anim * 9, 0, 9,
    35});
    sfSprite_setPosition(dart->sprite, (sfVector2f){dart->x, dart->y});
    sfSprite_setScale(dart->sprite, (sfVector2f){dart->z, dart->z});
    display_order(menu, dart, b);
}
