/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** mode.c
*/

#include "../include/my.h"

score_t *which_mode(menu_t *menu)
{
    if (menu->mode == 1)
        return my_hunter_wizard(menu);
    if (menu->mode == 2)
        return my_hunter_dart(menu);
    if (menu->mode == 3)
        return my_hunter_xtrem(menu);
}

static void check_button(sfMouseButtonEvent mouse, button_t *button,
    menu_t *menu, sfVector2u s)
{
    for (int i = 0; i < 2 && mouse.button == 0; i++)
        if (button->x[i] * (float)s.x / 1920 < (float)mouse.x
        && (button->x[i] + 261) * (float)s.x / 1920 > (float)mouse.x
        && button->y[i] * (float)s.y / 1010 < (float)mouse.y
        && (button->y[i] + 559) * (float)s.y / 1010 > (float)mouse.y) {
            sfSound_setVolume(button->music[0], menu->v_fx);
            sfSound_play(button->music[0]);
            menu->mode = i + 1;
        }
}

static void check_quit(sfMouseButtonEvent mouse, button_t *button,
    menu_t *menu, sfVector2u s)
{
    if (button->x[0] * (float)s.x / 1920 < (float)mouse.x
    && (button->x[0] + 266) * (float)s.x / 1920 > (float)mouse.x
    && button->y[0] * (float)s.y / 1010 < (float)mouse.y
    && (button->y[0] + 130) * (float)s.y / 1010 > (float)mouse.y
    && mouse.button == 0) {
        sfSound_setVolume(button->music[0], menu->v_fx);
        sfSound_play(button->music[0]);
        button->state[0] = 1;
        button->action = 1;
        sfClock_restart(button->clock);
    }
}

static void check_overmode(menu_t *menu, button_t *button, sfVector2u s)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(menu->window);

    for (int i = 0; i < 3; i++)
        if (button->x[i] * (float)s.x / 1920 < (float)mouse.x
        && (button->x[i] + 261) * (float)s.x / 1920 > (float)mouse.x
        && button->y[i] * (float)s.y / 1010 < (float)mouse.y
        && (button->y[i] + 559) * (float)s.y / 1010 > (float)mouse.y)
            button->state[i] = 1;
        else
            button->state[i] = 0;
}

static void check_events_mode(sfEvent e, menu_t *menu, button_t *button,
    button_t *quit)
{
    sfVector2u s = sfRenderWindow_getSize(menu->window);

    switch (e.type) {
        case (sfEvtClosed):
            sfRenderWindow_close(menu->window);
        case (sfEvtMouseButtonPressed):
            check_button(e.mouseButton, button, menu, s);
            check_quit(e.mouseButton, quit, menu, s);
            break;
        case (sfEvtKeyPressed):
            if (e.key.code == sfKeyEscape)
                menu->mode = -1;
            break;
        case (sfEvtResized):
            menu->size = s;
    }
    check_overmode(menu, button, s);
}

static void display_mode(sfRenderWindow *window, button_t *button)
{
    for (int i = 0; i < 3; i++) {
        sfSprite_setTextureRect(button->sprite\
        , (sfIntRect){261 * button->who[i], 559 * button->state[i], 261, 559});
        sfSprite_setPosition(button->sprite, (sfVector2f){button->x[i]\
        , button->y[i]});
        sfRenderWindow_drawSprite(window, button->sprite, NULL);
    }
}

static button_t *mode_button(menu_t *menu)
{
    button_t *button;

    button = malloc(sizeof(button_t));
    button->x[0] = 330;
    button->y[0] = 300;
    button->who[0] = 0;
    button->state[0] = 0;
    button->x[1] = 830;
    button->y[1] = 300;
    button->who[1] = 1;
    button->state[1] = 1;
    button->x[2] = 1330;
    button->y[2] = 300;
    button->who[2] = 2;
    button->state[2] = 0;
    button->music[0] = ALLOC_SOUND("sound/blabla1.ogg");
    button->sprite = ALLOC_SPRITE_P("sprite/mode.png");
    return button;
}

static button_t *choose_mode_quit(menu_t *menu)
{
    static button_t *button;

    button = malloc(sizeof(button_t));
    button->x[0] = 826.8;
    button->y[0] = 867;
    button->state[0] = 0;
    button->who[0] = 3;
    button->music[0] = ALLOC_SOUND("sound/click.ogg");
    button->clock = sfClock_create();
    button->action = 0;
    button->sprite = ALLOC_SPRITE_P("sprite/asset.png");
    sfSprite_setScale(button->sprite, (sfVector2f){1.2, 1.2});
    return button;
}

void choose_mode(menu_t *menu)
{
    sfEvent event;
    button_t *mode = mode_button(menu);
    button_t *quit = choose_mode_quit(menu);

    menu->mode = 0;
    while (sfRenderWindow_isOpen(menu->window) && menu->mode == 0) {
        while (sfRenderWindow_pollEvent(menu->window, &event))
            check_events_mode(event, menu, mode, quit);
        if (quit->action &&
        sfTime_asSeconds(sfClock_getElapsedTime(quit->clock)) > 0.25)
            menu->mode = -1;
        sfRenderWindow_clear(menu->window, sfBlack);
        grey_world(menu->window, menu->sprite);
        display_mode(menu->window, mode);
        display_button(menu->window, quit, 1);
        display_cursor(menu->window, menu->cursor);
        sfRenderWindow_display(menu->window);
    }
    if (sfRenderWindow_isOpen(menu->window) && menu->mode > 0)
        go_play(menu);
}
