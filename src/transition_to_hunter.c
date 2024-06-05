/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** transition_to_hunter.c
*/

#include "../include/my.h"

static void display_menu(sfRenderWindow *window, menu_t *menu)
{
    sfRenderWindow_drawSprite(window, menu->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->eric->sprite, NULL);
}

static int zoom(sfRenderWindow *window, menu_t *menu, sfClock *clock)
{
    sfEvent event;
    float i = 1.00;

    while (i < 1.36 && sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
            i = (event.type == sfEvtClosed) ? -1 : i;
        if (i == -1)
            return (84);
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 0.05) {
            i += 0.01;
            sfClock_restart(clock);
            eric_leave(menu, 1);
            sfSprite_setScale(menu->sprite, (sfVector2f){i, i});
            sfSprite_move(menu->sprite, (sfVector2f){-8, -8});
        }
        display_menu(window, menu);
        display_cursor(window, menu->cursor);
        sfRenderWindow_display(window);
    }
    return 0;
}

static int dezoom(sfRenderWindow *window, menu_t *menu, sfClock *clock)
{
    sfEvent event;
    float i = 1.37;

    while (i > 1.01 && sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
            i = (event.type == sfEvtClosed) ? -1 : i;
        if (i == -1)
            return (84);
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 0.05) {
            i -= 0.01;
            sfClock_restart(clock);
            eric_leave(menu, -1);
            sfSprite_setScale(menu->sprite, (sfVector2f){i, i});
            sfSprite_move(menu->sprite, (sfVector2f){8, 8});
        }
        display_menu(window, menu);
        display_cursor(window, menu->cursor);
        sfRenderWindow_display(window);
    }
    return salut_chef(menu->eric->music, menu);
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

static void check_events_end(menu_t *menu, sfEvent e, button_t *button)
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
            menu->size = s;
    }
}

static int go_again(menu_t *menu, score_t *s, end_t *eg\
    , button_t *button)
{
    int valuereturn = -1;
    greyworld_t *grey = NULL;

    if (button->action == 1) {
        valuereturn = 1;
        sfText_destroy(s->text);
    }
    if (button->action == 2) {
        grey = get_greyend(menu, s, eg);
        setting(menu, NULL, grey->sprite);
        sfTexture_destroy(grey->texture);
        sfSprite_destroy(grey->sprite);
    }
    if (button->action == 3) {
        valuereturn = 0;
        sfText_destroy(s->text);
    }
    button->state[button->action - 1] = 0;
    button->action = 0;
    return valuereturn;
}

static end_t *create_end(sfVector2u size, score_t *s, menu_t *menu)
{
    end_t *end = malloc(sizeof(end_t));
    sfFont *font = sfFont_createFromFile("font/Pentagon.ttf");

    end->sprite = ALLOC_SPRITE_P("sprite/Game_Over.png");
    sfSprite_setScale(end->sprite, (sfVector2f){0.7, 0.7});
    sfSprite_setPosition(end->sprite, (sfVector2f){680, 80});
    end->button = endgame_button(menu);
    end->score = malloc(sizeof(score_t));
    end->score->sprite = ALLOC_SPRITE_P("sprite/plate.png");
    end->score->text = sfText_create();
    end->score->text_score = my_strdup("Score\n000000");
    end->score->score = s->score;
    end->score->text_record = my_strdup("Highscore\n   000000");
    end->score->record = s->record;
    sfSprite_setScale(end->score->sprite, (sfVector2f){3.2, 3.2});
    sfText_setFont(end->score->text, font);
    sfText_setColor(end->score->text, (sfColor){255, 0, 0, 255});
    return end;
}

static int endgame_menu(menu_t *menu, score_t *s)
{
    sfEvent event;
    int go = -1;
    end_t *eg = create_end(sfRenderWindow_getSize(menu->window), s, menu);

    gameover(menu, s);
    while (sfRenderWindow_isOpen(menu->window) && go == -1 && s->score > -1) {
        while (sfRenderWindow_pollEvent(menu->window, &event))
            check_events_end(menu, event, eg->button);
        if (eg->button->action
        && sfTime_asSeconds(sfClock_getElapsedTime(eg->button->clock)) > 0.25)
            go = go_again(menu, s, eg, eg->button);
        sfRenderWindow_clear(menu->window, sfBlack);
        grey_world(menu->window, menu->sprite);
        sfRenderWindow_drawSprite(menu->window, eg->sprite, NULL);
        display_score(menu->window, eg->score);
        display_button(menu->window, eg->button, 3);
        display_cursor(menu->window, menu->cursor);
        sfRenderWindow_display(menu->window);
    }
    return go;
}

void go_play(menu_t *menu)
{
    sfClock *clock = sfClock_create();

    if (zoom(menu->window, menu, clock))
        sfRenderWindow_close(menu->window);
    while (endgame_menu(menu, which_mode(menu)) > 0);
    sfClock_restart(clock);
    sfSprite_setColor(menu->sprite, sfWhite);
    if (dezoom(menu->window, menu, clock))
        sfRenderWindow_close(menu->window);
    sfClock_destroy(clock);
}
