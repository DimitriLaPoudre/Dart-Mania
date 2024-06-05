/*
** EPITECH PROJECT, 2023
** src
** File description:
** setting.c
*/

#include "../include/my.h"

static void check_slider(menu_t *menu, sfVector2i mouse, sfVector2u s)
{
    if (menu->slider == 1) {
        menu->v_music = ((float)mouse.x * 1920 / (float)s.x - 843)\
        * 100 / 423.6;
        menu->v_music = (menu->v_music > 100) ? 100 : menu->v_music;
        menu->v_music = (menu->v_music < 0) ? 0 : menu->v_music;
        sfMusic_setVolume(menu->music, menu->v_music);
    } else if (menu->slider == 2) {
        menu->v_fx = ((float)mouse.x * 1920 / (float)s.x - 843) * 100 / 423.6;
        menu->v_fx = (menu->v_fx > 100) ? 100 : menu->v_fx;
        menu->v_fx = (menu->v_fx < 0) ? 0 : menu->v_fx;
    }
    for (int i = 0; i < 2 && menu->slider == 0; i++)
        if (843 * (float)s.x / 1920 < (float)mouse.x
        && (843 + 423.6) * (float)s.x / 1920 > (float)mouse.x
        && (434 + 100 * i) * (float)s.y / 1010 < (float)mouse.y
        && ((434 + 100 * i) + 46) * (float)s.y / 1010 > (float)mouse.y) {
            menu->slider = i + 1;
    }
}

static void check_button(sfMouseButtonEvent mouse, menu_t *menu,
    button_t *button, sfVector2u s)
{
    if (button->x[0] * (float)s.x / 1920 < (float)mouse.x
    && (button->x[0] + 333) * (float)s.x / 1920 > (float)mouse.x
    && button->y[0] * (float)s.y / 1010 < (float)mouse.y
    && (button->y[0] + 155) * (float)s.y / 1010 > (float)mouse.y
    && mouse.button == 0) {
        button->action = 1;
        sfSound_setVolume(button->music[0], menu->v_fx);
        sfSound_play(button->music[0]);
        button->state[0] = 1;
        sfClock_restart(button->clock);
    }
    for (int i = 0; i < 4 && mouse.button == 0; i++)
        if ((747 + 120 * i) * (float)s.x / 1920 < (float)mouse.x
        && ((747 + 120 * i) + 64) * (float)s.x / 1920 > (float)mouse.x
        && 718 * (float)s.y / 1010 < (float)mouse.y
        && (718 + 64) * (float)s.y / 1010 > (float)mouse.y) {
            menu->fps = (15 * my_power(2,
            (i + 1) % 4) == 15) ? 0 : 15 * my_power(2, (i + 1) % 4);
            sfRenderWindow_setFramerateLimit(menu->window, menu->fps);
        }
}

static void check_help(sfMouseButtonEvent mouse, menu_t *menu,
    button_t *button, sfVector2u s)
{
    if (mouse.button == 0) {
        check_button(mouse, menu, button, s);
        check_slider(menu, sfMouse_getPositionRenderWindow(menu->window), s);
    }
}

static void check_key(sfKeyCode key, button_t *button, menu_t *menu)
{
    int i = -1;

    if ((key == sfKeyEscape || key == sfKeyEscape) && button->action == 0)
        i = 0;
    if (i != -1) {
        button->action = 1;
        sfSound_setVolume(button->music[0], menu->v_fx);
        sfSound_play(button->music[0]);
        button->state[0] = 1;
        sfClock_restart(button->clock);
    }
}

static void help_resize(menu_t *menu, all_b_t *b, sfVector2u s)
{
    if (b != NULL) {
        b->ballon->x = b->ballon->x * (float)s.x / (float)menu->size.x;
        b->ballon->y = b->ballon->y * (float)s.y / (float)menu->size.y;
        b->boom->x = b->boom->x * (float)s.x / (float)menu->size.x;
        b->boom->y = b->boom->y * (float)s.y / (float)menu->size.y;
    }
}

static void check_events_setting(menu_t *menu, sfEvent e, button_t *button,
    all_b_t *b)
{
    sfVector2u s = sfRenderWindow_getSize(menu->window);

    switch (e.type) {
        case (sfEvtClosed):
            sfRenderWindow_close(menu->window);
        case (sfEvtMouseButtonPressed):
            check_help(e.mouseButton, menu, button, s);
            break;
        case (sfEvtMouseButtonReleased):
            menu->slider = 0;
            break;
        case (sfEvtKeyPressed):
            check_key(e.key.code, button, menu);
            break;
        case (sfEvtResized):
            help_resize(menu, b, s);
            menu->size = s;
    }
    if (menu->slider)
        check_slider(menu, sfMouse_getPositionRenderWindow(menu->window), s);
}

static sfSprite *create_setting(void)
{
    sfSprite *sprite = ALLOC_SPRITE_P("sprite/setting.png");

    sfSprite_setScale(sprite, (sfVector2f){2, 2});
    sfSprite_setPosition(sprite, (sfVector2f){603, 300});
    return sprite;
}

static void display_fps(menu_t *menu)
{
    static sfSprite *check = NULL;
    int i;

    if (check == NULL) {
        check = ALLOC_SPRITE_P("sprite/check.png");
        sfSprite_setScale(check, (sfVector2f){2, 2});
    }
    if (menu->fps == 30)
        i = 0;
    if (menu->fps == 60)
        i = 1;
    if (menu->fps == 120)
        i = 2;
    if (menu->fps == 0)
        i = 3;
    sfSprite_setPosition(check, (sfVector2f){747 + 120 * i, 718});
    sfRenderWindow_drawSprite(menu->window, check, NULL);
}

static void display_volume(menu_t *menu)
{
    static sfSprite *volume = NULL;
    int i;

    if (volume == NULL) {
        volume = ALLOC_SPRITE_P("sprite/volume.png");
        sfSprite_setScale(volume, (sfVector2f){2, 2});
    }
    sfSprite_setPosition(volume, (sfVector2f){843, 434});
    sfSprite_setScale(volume,
    (sfVector2f){menu->v_music * 1.412, 2});
    sfRenderWindow_drawSprite(menu->window, volume, NULL);
    sfSprite_setPosition(volume, (sfVector2f){843, 534});
    sfSprite_setScale(volume,
    (sfVector2f){menu->v_fx * 1.412, 2});
    sfRenderWindow_drawSprite(menu->window, volume, NULL);
}

void setting(menu_t *menu, all_b_t *b, sfSprite *bg)
{
    sfEvent event;
    int go = -1;
    sfSprite *sprite = create_setting();
    button_t *quit = setting_quit(menu);

    while (sfRenderWindow_isOpen(menu->window) && go == -1) {
        while (sfRenderWindow_pollEvent(menu->window, &event))
            check_events_setting(menu, event, quit, b);
        if (quit->action &&
        sfTime_asSeconds(sfClock_getElapsedTime(quit->clock)) > 0.25)
            return;
        sfRenderWindow_clear(menu->window, sfBlack);
        sfRenderWindow_drawSprite(menu->window, bg, NULL);
        sfRenderWindow_drawSprite(menu->window, sprite, NULL);
        display_fps(menu);
        display_volume(menu);
        display_button(menu->window, quit, 1);
        display_cursor(menu->window, menu->cursor);
        sfRenderWindow_display(menu->window);
    }
}
