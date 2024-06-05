/*
** EPITECH PROJECT, 2023
** lib/hunter
** File description:
** use_score.c
*/

#include "../../include/my.h"

static void get_str(int nb, char *str)
{
    for (int i = 0; nb > 0; i++) {
        *(str + 5 - i) = nb % 10 + 48;
        nb /= 10;
    }
}

void grey_world(sfRenderWindow *window, sfSprite *sprite)
{
    sfRenderWindow_clear(window, sfBlack);
    sfSprite_setColor(sprite, (sfColor){255, 255, 255, 100});
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_setColor(sprite, sfWhite);
}

greyworld_t *get_greyend(menu_t *menu, score_t *s, end_t *eg)
{
    sfVector2u size = sfRenderWindow_getSize(menu->window);
    greyworld_t *grey = malloc(sizeof(greyworld_t));

    sfRenderWindow_clear(menu->window, sfBlack);
    sfRenderWindow_drawSprite(menu->window, menu->sprite, NULL);
    sfRenderWindow_drawSprite(menu->window, eg->sprite, NULL);
    display_score(menu->window, s);
    grey->texture = sfTexture_create(size.x, size.y);
    sfTexture_updateFromRenderWindow(grey->texture, menu->window, 0, 0);
    grey->sprite = sfSprite_create();
    sfSprite_setTexture(grey->sprite, grey->texture, sfFalse);
    sfSprite_setScale(grey->sprite,
    (sfVector2f){sfSprite_getScale(grey->sprite).x * 1920 / (int)size.x,
    sfSprite_getScale(grey->sprite).y * 1010 / (int)size.y});
    sfSprite_setColor(grey->sprite, (sfColor){255, 255, 255, 100});
    return grey;
}

void gameover(menu_t *menu, score_t *s)
{
    static sfSound *gameover = NULL;
    int fd;
    char *path[3] = {"save/highscore_wizard", "save/highscore_dart",
    "save/highscore_xtrem"};

    if (s->score == -1)
        return;
    if (gameover == NULL) {
        gameover = ALLOC_SOUND("sound/gameover.ogg");
    }
    sfMusic_stop(menu->music);
    sfSound_setVolume(gameover, menu->v_fx);
    sfSound_play(gameover);
    if (s->score >= s->record) {
        fd = open(path[menu->mode - 1], O_RDWR);
        write(fd, s->text_score + 6, 6);
        close(fd);
    }
}

void display_score(sfRenderWindow *window, score_t *s)
{
    sfSprite_setPosition(s->sprite, (sfVector2f){20, 100});
    sfRenderWindow_drawSprite(window, s->sprite, NULL);
    get_str(s->record, &(s->text_record[13]));
    sfText_setPosition(s->text, (sfVector2f){45, 210});
    sfText_setString(s->text, s->text_record);
    sfText_setCharacterSize(s->text, 45);
    sfRenderWindow_drawText(window, s->text, NULL);
    sfSprite_setPosition(s->sprite, (sfVector2f){20, -60});
    sfRenderWindow_drawSprite(window, s->sprite, NULL);
    get_str(s->score, &(s->text_score[6]));
    sfText_setPosition(s->text, (sfVector2f){70, 40});
    sfText_setString(s->text, s->text_score);
    sfText_setCharacterSize(s->text, 55);
    sfRenderWindow_drawText(window, s->text, NULL);
}

void display_hud(sfRenderWindow *window\
    , score_t *s, life_t *l)
{
    float time = sfTime_asSeconds(sfClock_getElapsedTime(l->clock));
    int btm = 14 * floor(rand() % 4);

    display_score(window, s);
    for (int i = 0; i < l->life; i++) {
        sfSprite_setPosition(l->sprite, (sfVector2f){1800 - i * 100, 720});
        if (time > 0.2) {
            sfSprite_setTextureRect(l->sprite, (sfIntRect)\
            {btm, 0, 14, 28});
            sfClock_restart(l->clock);
        }
        sfRenderWindow_drawSprite(window, l->sprite, NULL);
    }
}
