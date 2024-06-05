/*
** EPITECH PROJECT, 2023
** my first graph
** File description:
** my first graph project
*/

#include "../include/my.h"

score_t *my_hunter_wizard(menu_t *menu)
{
    sfEvent event;
    all_b_t *b = create_b(sfRenderWindow_getSize(menu->window), menu);

    if (sfMusic_getStatus(menu->music) == sfStopped)
        sfMusic_play(menu->music);
    while (sfRenderWindow_isOpen(menu->window) && b->ballon->l->life > 0) {
        while (sfRenderWindow_pollEvent(menu->window, &event))
            check_events(event, b, menu);
        sfRenderWindow_clear(menu->window, sfBlack);
        sfRenderWindow_drawSprite(menu->window, menu->sprite, NULL);
        display_b(menu->window, b);
        display_cursor(menu->window, menu->cursor);
        display_hud(menu->window, b->ballon->s, b->ballon->l);
        sfRenderWindow_display(menu->window);
    }
    return b->ballon->s;
}

score_t *my_hunter_dart(menu_t *menu)
{
    sfEvent event;
    all_b_t *b = create_b(sfRenderWindow_getSize(menu->window), menu);
    dart_t *dart = create_dart(menu);

    if (sfMusic_getStatus(menu->music) == sfStopped)
        sfMusic_play(menu->music);
    while (sfRenderWindow_isOpen(menu->window) && b->ballon->l->life > 0) {
        while (sfRenderWindow_pollEvent(menu->window, &event))
            check_events_dart(event, b, dart, menu);
        sfRenderWindow_clear(menu->window, sfBlack);
        sfRenderWindow_drawSprite(menu->window, menu->sprite, NULL);
        display_dart(menu, dart, b);
        display_cursor(menu->window, menu->cursor);
        display_hud(menu->window, b->ballon->s, b->ballon->l);
        sfRenderWindow_display(menu->window);
    }
    return b->ballon->s;
}

score_t *my_hunter_xtrem(menu_t *menu)
{
    sfEvent event;
    all_b_t *b = create_b(sfRenderWindow_getSize(menu->window), menu);

    if (sfMusic_getStatus(menu->music) == sfStopped)
        sfMusic_play(menu->music);
    while (sfRenderWindow_isOpen(menu->window) && b->ballon->l->life > 0) {
        while (sfRenderWindow_pollEvent(menu->window, &event))
            check_events(event, b, menu);
        sfRenderWindow_clear(menu->window, sfBlack);
        sfRenderWindow_drawSprite(menu->window, menu->sprite, NULL);
        display_b(menu->window, b);
        display_cursor(menu->window, menu->cursor);
        display_hud(menu->window, b->ballon->s, b->ballon->l);
        sfRenderWindow_display(menu->window);
    }
    return b->ballon->s;
}
