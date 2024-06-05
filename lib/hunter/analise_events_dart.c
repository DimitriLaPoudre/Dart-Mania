/*
** EPITECH PROJECT, 2023
** lib/hunter
** File description:
** analise_events.c
*/

#include "../../include/my.h"

static void set_dart(menu_t *menu, sfEvent e, dart_t *dart, sfVector2u s)
{
    sfVector2f dest = {0, 0};

    if (e.mouseButton.button == 0 && dart->state == 0) {
        get_position(&dest.x, &dest.y, menu->window);
        dart->state = 1;
        dart->dist = sqrt(pow(dart->x - dest.x, 2)\
        + pow(dest.y - dart->y, 2)) - 30;
        dart->angle = atan2(960.0 - dest.x, 1030 - dest.y) \
        * (180.0 / M_PI);
        dart->angle = -(dart->angle);
        dart->y -= 30 * cos(dart->angle * M_PI / 180);
        dart->x += 30 * sin(dart->angle * M_PI / 180);
        sfClock_restart(dart->clockmove);
        sfSound_setVolume(dart->sound, menu->v_fx);
        sfSound_play(dart->sound);
    }
}

static void help_resize(menu_t *menu, all_b_t *b, dart_t *dart, sfVector2u s)
{
    b->ballon->x = b->ballon->x * (float)s.x / (float)menu->size.x;
    b->ballon->y = b->ballon->y * (float)s.y / (float)menu->size.y;
}

void check_events_dart(sfEvent event, all_b_t *b, dart_t *dart, menu_t *menu)
{
    sfVector2u s = sfRenderWindow_getSize(menu->window);

    switch (event.type) {
        case (sfEvtClosed):
            sfRenderWindow_close(menu->window);
        case (sfEvtMouseButtonPressed):
            set_dart(menu, event, dart, s);
            break;
        case (sfEvtKeyPressed):
            if (event.key.code == sfKeySpace || event.key.code == sfKeyEscape)
                menu_pause(b, menu, dart);
            break;
        case (sfEvtLostFocus):
            menu_pause(b, menu, dart);
            break;
        case (sfEvtResized):
            help_resize(menu, b, dart, s);
            menu->size = s;
    }
}
