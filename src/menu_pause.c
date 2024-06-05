/*
** EPITECH PROJECT, 2023
** lib/hunter
** File description:
** menu_pause.c
*/

#include "../include/my.h"

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

static void check_events_pause(menu_t *menu, sfEvent e,
    button_t *button, all_b_t *b)
{
    sfVector2u s = sfRenderWindow_getSize(menu->window);

    switch (e.type) {
        case (sfEvtClosed):
            sfRenderWindow_close(menu->window);
            break;
        case (sfEvtMouseButtonPressed):
            check_button(e.mouseButton, menu, button, s);
            break;
        case (sfEvtKeyPressed):
            check_key(e.key.code, button, menu);
        case (sfEvtResized):
            b->ballon->x = b->ballon->x * (float)s.x / (float)menu->size.x;
            b->ballon->y = b->ballon->y * (float)s.y / (float)menu->size.y;
            b->boom->x = b->boom->x * (float)s.x / (float)menu->size.x;
            b->boom->y = b->boom->y * (float)s.y / (float)menu->size.y;
            menu->size = s;
            break;
    }
}

static int go_back(menu_t *menu, sfSprite *sprite, button_t *button,
    all_b_t *b)
{
    int valuereturn = -1;

    if (button->action == 1)
        valuereturn = 0;
    if (button->action == 2)
        setting(menu, b, sprite);
    if (button->action == 3) {
        b->ballon->l->life = 0;
        b->ballon->s->score = -1;
        valuereturn = 0;
    }
    button->state[button->action - 1] = 0;
    button->action = 0;
    return valuereturn;
}

pause_t *create_pause(sfVector2u size, menu_t *menu,
    all_b_t *b, dart_t *dart)
{
    pause_t *pause = malloc(sizeof(pause_t));

    sfRenderWindow_clear(menu->window, sfBlack);
    sfRenderWindow_drawSprite(menu->window, menu->sprite, NULL);
    if (dart != NULL)
        display_order(menu, dart, b);
    else
        display_b(menu->window, b);
    display_hud(menu->window, b->ballon->s, b->ballon->l);
    pause->texture = sfTexture_create(size.x, size.y);
    sfTexture_updateFromRenderWindow(pause->texture, menu->window, 0, 0);
    pause->sprite = sfSprite_create();
    sfSprite_setTexture(pause->sprite, pause->texture, sfFalse);
    sfSprite_setScale(pause->sprite,
    (sfVector2f){sfSprite_getScale(pause->sprite).x * 1920 / (int)size.x,
    sfSprite_getScale(pause->sprite).y * 1010 / (int)size.y});
    sfSprite_setColor(pause->sprite, (sfColor){255, 255, 255, 100});
    pause->button = pause_button(menu);
    return pause;
}

static void bye(all_b_t *b, pause_t *pause, dart_t *dart)
{
    sfTexture_destroy(pause->texture);
    sfSprite_destroy(pause->sprite);
    free(pause);
    sfClock_restart(b->boom->clock);
    sfClock_restart(b->ballon->clockanim);
    sfClock_restart(b->ballon->clockmove);
    if (dart != NULL)
        sfClock_restart(dart->clockmove);
}

void menu_pause(all_b_t *b, menu_t *menu, dart_t *dart)
{
    sfEvent event;
    int go = -1;
    pause_t *pause = create_pause(sfRenderWindow_getSize(menu->window), menu,
    b, dart);

    while (sfRenderWindow_isOpen(menu->window) && go == -1) {
        while (sfRenderWindow_pollEvent(menu->window, &event))
            check_events_pause(menu, event, pause->button, b);
        if (pause->button->action &&
        sfTime_asSeconds(sfClock_getElapsedTime(pause->button->clock)) > 0.25)
            go = go_back(menu, pause->sprite, pause->button, b);
        sfRenderWindow_clear(menu->window, sfBlack);
        sfRenderWindow_drawSprite(menu->window, pause->sprite, NULL);
        display_score(menu->window, b->ballon->s);
        display_button(menu->window, pause->button, 3);
        display_cursor(menu->window, menu->cursor);
        sfRenderWindow_display(menu->window);
    }
    bye(b, pause, dart);
    return;
}
