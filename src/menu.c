/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** menu.c
*/

#include "../include/my.h"

static sfRenderWindow *create_window(void)
{
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode) {1920, 1080,
    32}, "Dart Mania", sfDefaultStyle, NULL);
    sfImage* Icon = sfImage_createFromFile("sprite/icon.png");

    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfRenderWindow_setIcon(window, 100, 100, sfImage_getPixelsPtr(Icon));
    sfImage_destroy(Icon);
    return window;
}

static menu_t *create_menu(void)
{
    menu_t *menu;

    menu = malloc(sizeof(menu_t));
    menu->window = create_window();
    menu->sprite = ALLOC_SPRITE_P("sprite/menu.png");
    menu->size = sfRenderWindow_getSize(menu->window);
    menu->eric = create_eric(menu->size, menu);
    menu->music = sfMusic_createFromFile("sound/theme.ogg");
    sfSprite_setOrigin(menu->sprite, (sfVector2f){293, 291});
    sfSprite_setPosition(menu->sprite, (sfVector2f){293, 291});
    sfMusic_setLoop(menu->music, sfTrue);
    sfMusic_play(menu->music);
    menu->cursor = create_cursor();
    menu->fps = 60;
    sfRenderWindow_setFramerateLimit(menu->window, 60);
    menu->v_music = 21.0;
    sfMusic_setVolume(menu->music, menu->v_music);
    menu->v_fx = 100.0;
    menu->slider = 0;
    return menu;
}

static void check_button(sfMouseButtonEvent mouse, menu_t *menu,
    button_t *button, sfVector2u s)
{
    for (int i = 0; i < 3 && button->action == 0 && mouse.button == 0; i++)
        if (button->x[i] * (float)s.x / 1920 < (float)mouse.x
        && (button->x[i] + 333) * (float)s.x / 1920 > (float)mouse.x
        && button->y[i] * (float)s.y / 1010 < (float)mouse.y
        && (button->y[i] + 155) * (float)s.y / 1010 > (float)mouse.y) {
            button->action = i + 1;
            sfSound_setVolume(button->music[i], menu->v_fx);
            sfSound_play(button->music[i]);
            button->state[i] = 1;
            sfClock_restart(button->clock);
        }
}

static void check_key(sfKeyCode key, button_t *button, menu_t *menu)
{
    int i = -1;

    if (key == sfKeySpace && button->action == 0)
        i = 0;
    if (key == sfKeyEscape && button->action == 0)
        i = 2;
    if (i != -1) {
        button->action = i + 1;
        sfSound_setVolume(button->music[i], menu->v_fx);
        sfSound_play(button->music[i]);
        button->state[i] = 1;
        sfClock_restart(button->clock);
    }
}

static void check_events_menu(sfEvent e, button_t *button, menu_t *menu)
{
    sfVector2u s = sfRenderWindow_getSize(menu->window);

    switch (e.type) {
        case (sfEvtClosed):
            sfRenderWindow_close(menu->window);
            break;
        case (sfEvtMouseButtonPressed):
            check_button(e.mouseButton, menu, button, s);
            eric_shot(s, e.mouseButton, menu);
            break;
        case (sfEvtKeyPressed):
            check_key(e.key.code, button, menu);
        case (sfEvtResized):
            menu->size = s;
            break;
    }
}

static void display_menu(sfRenderWindow *window, sfSprite *menu\
    , sfSprite *eric, button_t *button)
{
    sfRenderWindow_drawSprite(window, menu, NULL);
    sfRenderWindow_drawSprite(window, eric, NULL);
    display_button(window, button, 3);
}

static void lets_go(menu_t *menu, button_t *button)
{
    if (button->action == 1) {
        choose_mode(menu);
        sfMusic_play(menu->music);
    }
    if (button->action == 2)
        setting(menu, NULL, menu->sprite);
    if (button->action == 3) {
        while (sfSound_getStatus(button->music[2]) == sfPlaying);
        sfSound_stop(button->music[2]);
        sfRenderWindow_close(menu->window);
    }
    button->state[button->action - 1] = 0;
    button->action = 0;
}

void menu(void)
{
    sfEvent event;
    menu_t *menu = create_menu();
    button_t *button = menu_button(menu);

    while (sfRenderWindow_isOpen(menu->window)) {
        while (sfRenderWindow_pollEvent(menu->window, &event))
            check_events_menu(event, button, menu);
        if (button->action
        && sfTime_asSeconds(sfClock_getElapsedTime(button->clock)) > 0.25)
            lets_go(menu, button);
        sfRenderWindow_clear(menu->window, sfBlack);
        display_menu(menu->window, menu->sprite, menu->eric->sprite, button);
        display_cursor(menu->window, menu->cursor);
        sfRenderWindow_display(menu->window);
    }
    destroyer(menu->window, button->clock, menu->music);
}
