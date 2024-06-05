/*
** EPITECH PROJECT, 2023
** lib/hunter
** File description:
** use_button.c
*/

#include "../../include/my.h"

button_t *setting_quit(menu_t *menu)
{
    static button_t *button;

    button = malloc(sizeof(button_t));
    button->x[0] = 793.5;
    button->y[0] = (827);
    button->state[0] = 0;
    button->who[0] = 3;
    button->music[0] = ALLOC_SOUND("sound/click.ogg");
    button->clock = sfClock_create();
    button->action = 0;
    button->sprite = ALLOC_SPRITE_P("sprite/asset.png");
    sfSprite_setScale(button->sprite, (sfVector2f){1.5, 1.5});
    return button;
}

button_t *menu_button(menu_t *menu)
{
    static button_t *button;

    button = malloc(sizeof(button_t));
    for (int i = 0; i < 3; i++) {
        button->x[i] = 793.5;
        button->y[i] = (367 + 180 * i);
        button->state[i] = 0;
    }
    button->who[0] = 0;
    button->music[0] = ALLOC_SOUND("sound/ze parti.ogg");
    button->who[1] = 4;
    button->music[1] = ALLOC_SOUND("sound/setting.ogg");
    button->who[2] = 3;
    button->music[2] = ALLOC_SOUND("sound/degage.ogg");
    button->clock = sfClock_create();
    button->action = 0;
    button->sprite = ALLOC_SPRITE_P("sprite/asset.png");
    sfSprite_setScale(button->sprite, (sfVector2f){1.5, 1.5});
    return button;
}

button_t *pause_button(menu_t *menu)
{
    static button_t *button;

    button = malloc(sizeof(button_t));
    for (int i = 0; i < 3; i++) {
        button->x[i] = 793.5;
        button->y[i] = (367 + 180 * i);
        button->state[i] = 0;
    }
    button->who[0] = 1;
    button->music[0] = ALLOC_SOUND("sound/ok lets go.ogg");
    button->who[1] = 4;
    button->music[1] = ALLOC_SOUND("sound/setting.ogg");
    button->who[2] = 2;
    button->music[2] = ALLOC_SOUND("sound/blank.ogg");
    button->clock = sfClock_create();
    button->action = 0;
    button->sprite = ALLOC_SPRITE_P("sprite/asset.png");
    sfSprite_setScale(button->sprite, (sfVector2f){1.5, 1.5});
    return button;
}

button_t *endgame_button(menu_t *menu)
{
    static button_t *button;

    button = malloc(sizeof(button_t));
    for (int i = 0; i < 3; i++) {
        button->x[i] = 793.5;
        button->y[i] = (367 + 180 * i);
        button->state[i] = 0;
    }
    button->who[0] = 0;
    button->music[0] = ALLOC_SOUND("sound/rejouer.ogg");
    button->who[1] = 4;
    button->music[1] = ALLOC_SOUND("sound/setting.ogg");
    button->who[2] = 2;
    button->music[2] = ALLOC_SOUND("sound/blank.ogg");
    button->clock = sfClock_create();
    button->action = 0;
    button->sprite = ALLOC_SPRITE_P("sprite/asset.png");
    sfSprite_setScale(button->sprite, (sfVector2f){1.5, 1.5});
    return button;
}

void display_button(sfRenderWindow *window, button_t *button, int nb)
{
    for (int i = 0; i < nb; i++) {
        sfSprite_setTextureRect(button->sprite\
        , (sfIntRect){222 * button->state[i], 108 * button->who[i], 222, 108});
        sfSprite_setPosition(button->sprite, (sfVector2f){button->x[i]\
        , button->y[i]});
        sfRenderWindow_drawSprite(window, button->sprite, NULL);
    }
}
