/*
** EPITECH PROJECT, 2023
** lib/hunter
** File description:
** analise_events.c
*/

#include "../../include/my.h"

static void missed(int *life, menu_t *menu)
{
    static sfSound *missed = NULL;

    if (missed == NULL)
        missed = ALLOC_SOUND("sound/a cote.ogg");
    if (*life != 1) {
        sfSound_setVolume(missed, menu->v_fx);
        sfSound_play(missed);
    } else
        sfSound_stop(missed);
    *life -= 1;
}

static void check_ballon(menu_t *menu, sfEvent event, all_b_t *b,
    sfVector2u s)
{
    if (b->ballon->x < (float)event.mouseButton.x
        && b->ballon->x + (16 * b->ballon->z) * (float)s.x / 1920 > (float)\
        event.mouseButton.x
        && b->ballon->y < (float)event.mouseButton.y
        && b->ballon->y + (19 * b->ballon->z) * (float)s.y / 1010 > (float)\
        event.mouseButton.y && event.mouseButton.button == 0) {
        reset_boom(b->boom, b->ballon, menu);
        reset_ballon(b->ballon, sfRenderWindow_getSize(menu->window));
        b->ballon->s->score++;
        if (b->ballon->s->score > b->ballon->s->record)
            b->ballon->s->record++;
    } else if (event.mouseButton.button == 0)
        missed(&(b->ballon->l->life), menu);
}

void check_events(sfEvent event, all_b_t *b, menu_t *menu)
{
    sfVector2u s = sfRenderWindow_getSize(menu->window);

    switch (event.type) {
        case (sfEvtClosed):
            sfRenderWindow_close(menu->window);
        case (sfEvtMouseButtonPressed):
            check_ballon(menu, event, b, s);
            break;
        case (sfEvtKeyPressed):
            if (event.key.code == sfKeySpace || event.key.code == sfKeyEscape)
                menu_pause(b, menu, NULL);
            break;
        case (sfEvtLostFocus):
            menu_pause(b, menu, NULL);
            break;
        case (sfEvtResized):
            b->ballon->x = b->ballon->x * (float)s.x / (float)menu->size.x;
            b->ballon->y = b->ballon->y * (float)s.y / (float)menu->size.y;
            menu->size = s;
    }
}
