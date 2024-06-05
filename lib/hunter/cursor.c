/*
** EPITECH PROJECT, 2023
** lib/my
** File description:
** cursor.c
*/

#include "../../include/my.h"

cursor_t *create_cursor(void)
{
    cursor_t *cursor;

    cursor = malloc(sizeof(cursor_t));
    cursor->sprite = ALLOC_SPRITE_P("sprite/hand_l.png");
    sfSprite_setOrigin(cursor->sprite, (sfVector2f){241, 0});
    return cursor;
}

void get_position(float *x, float *y, sfRenderWindow *window)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);
    sfVector2u size = sfRenderWindow_getSize(window);

    *x = (float)pos.x * 1920 / size.x;
    *y = (float)pos.y * 1010 / size.y;
    *x = (*x > 1920) ? 1920 : *x;
    *x = (*x < 0) ? 0 : *x;
    *y = (*y > 1010) ? 1010 : *y;
    *y = (*y < 0) ? 0 : *y;
}

void display_cursor(sfRenderWindow *window, cursor_t *cursor)
{
    float angle;
    float x = 0;
    float y = 0;

    get_position(&x, &y, window);
    sfSprite_setPosition(cursor->sprite, (sfVector2f){x, y});
    sfSprite_setScale(cursor->sprite, (sfVector2f){7, 7});
    angle = atan2(abs(550.0 - x), abs(1200 - y)) \
    * (180.0 / M_PI);
    if (550.0 - x > 0)
        angle = -angle;
    sfSprite_setRotation(cursor->sprite, angle - 38);
    sfRenderWindow_drawSprite(window, cursor->sprite, NULL);
}
