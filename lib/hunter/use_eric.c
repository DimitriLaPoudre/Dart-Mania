/*
** EPITECH PROJECT, 2023
** lib/hunter
** File description:
** use_eric.c
*/

#include "../../include/my.h"

void eric_shot(sfVector2u size, sfMouseButtonEvent mouse, menu_t *menu)
{
    sfFloatRect hitbox1 = {1306 * (float)size.x / 1920 + 100,
    362 * (float)size.y / 1010, 130, 170};
    sfFloatRect hitbox2 = {1306 * (float)size.x / 1920,
    362 * (float)size.y / 1010 + 170, 410, 350};
    static sfSound *fiuu = NULL;

    if (fiuu == NULL)
        fiuu = ALLOC_SOUND("sound/pas sur eric.ogg");
    if (sfFloatRect_contains(&hitbox1, mouse.x, mouse.y)
    || sfFloatRect_contains(&hitbox2, mouse.x, mouse.y)) {
        sfSound_setVolume(fiuu, menu->v_fx);
        sfSound_play(fiuu);
    }
}

void eric_leave(menu_t *menu, int d)
{
    sfVector2f scale = sfSprite_getScale(menu->eric->sprite);

    sfSprite_setScale(menu->eric->sprite,
    (sfVector2f){scale.x + 0.01 * d, scale.y + 0.01 * d});
    sfSprite_move(menu->eric->sprite,
    (sfVector2f){2.2 * d + 15 * d, -7.3 * d});
    if (d == 1)
        sfSprite_setTextureRect(menu->eric->sprite,
        (sfIntRect){406, 0, 406, 520});
    else
        sfSprite_setTextureRect(menu->eric->sprite,
        (sfIntRect){0, 0, 406, 520});
}

int salut_chef(sfSound *music, menu_t *menu)
{
    sfSound_setVolume(music, menu->v_fx);
    sfSound_play(music);
    return 0;
}

eric_t *create_eric(sfVector2u size, menu_t *menu)
{
    eric_t *eric;

    eric = malloc(sizeof(eric_t));
    eric->x = 1306 * (float)size.x / 1920;
    eric->y = 362 * (float)size.y / 1010;
    eric->d = 0;
    eric->sprite = ALLOC_SPRITE_P("sprite/erik.png");
    sfSprite_setTextureRect(eric->sprite\
    , (sfIntRect){406 * eric->d, 0, 406, 520});
    sfSprite_setPosition(eric->sprite, (sfVector2f){eric->x, eric->y});
    eric->music = ALLOC_SOUND("sound/salut chef.ogg");
    return eric;
}
