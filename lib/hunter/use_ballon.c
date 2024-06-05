/*
** EPITECH PROJECT, 2023
** lib/hunter
** File description:
** create_ballon.c
*/

#include "../../include/my.h"

static void get_record(ballon_t *ballon, short mode)
{
    struct stat info;
    int fd;
    char buffer[7] = {'\0'};
    char *zero = "000000";
    char *path[3] = {"save/highscore_wizard", "save/highscore_dart",
    "save/highscore_xtrem"};

    fd = open(path[mode - 1], O_RDONLY | O_CREAT, 0777);
    read(fd, buffer, 6);
    ballon->s->record = my_getnbr(buffer);
    close(fd);
    if (buffer[0] == '\0') {
        fd = open(path[mode - 1], O_WRONLY | O_NONBLOCK);
        write(fd, zero, 6);
        close(fd);
    }
}

static void help_create_ballon2(ballon_t *ballon)
{
    ballon->l = malloc(sizeof(life_t));
    ballon->l->sprite = ALLOC_SPRITE_P("sprite/Life.png");
    ballon->l->life = 3;
    ballon->l->anim = 0;
    ballon->l->clock = ALLOC_CLOCK;
    sfSprite_setScale(ballon->l->sprite, (sfVector2f){6.0, 6.0});
}

static void help_create_ballon(ballon_t *ballon, menu_t *menu)
{
    sfFont *font = sfFont_createFromFile("font/Pentagon.ttf");

    ballon->clockanim = ALLOC_CLOCK;
    ballon->clockmove = ALLOC_CLOCK;
    ballon->s = malloc(sizeof(score_t));
    ballon->s->sprite = ALLOC_SPRITE_P("sprite/plate.png");
    ballon->s->text = sfText_create();
    ballon->s->text_score = my_strdup("Score\n000000");
    ballon->s->score = 0;
    ballon->s->text_record = my_strdup("Highscore\n   000000");
    get_record(ballon, menu->mode);
    sfText_setFont(ballon->s->text, font);
    sfText_setColor(ballon->s->text, (sfColor){255, 0, 0, 255});
    sfSprite_setScale(ballon->s->sprite, (sfVector2f){3.2, 3.2});
    help_create_ballon2(ballon);
}

ballon_t *create_ballon(sfVector2u size, menu_t *menu)
{
    static ballon_t *ballon;

    ballon = malloc(sizeof(ballon_t));
    srand(time(NULL));
    ballon->d = rand() % 2;
    ballon->z = 5 + (double)rand() * 2 / RAND_MAX;
    ballon->y = (rand() % 486 - (40 * (ballon->z - 5)) + 120)\
    * (int)size.y / 1010;
    ballon->r = 100 + rand() % 156;
    ballon->g = 100 + rand() % 156;
    ballon->b = 100 + rand() % 156;
    ballon->sprite = ALLOC_SPRITE_P("sprite/ballon.png");
    ballon->anim = 0;
    ballon->x = -(16 * ballon->z + 81);
    ballon->x += ((int)size.x + 80 + -ballon->x) * ballon->d;
    sfSprite_setScale(ballon->sprite, (sfVector2f){ballon->z, ballon->z});
    help_create_ballon(ballon, menu);
    return ballon;
}

all_b_t *create_b(sfVector2u size, menu_t *menu)
{
    all_b_t *b = malloc(sizeof(all_b_t));

    b->ballon = create_ballon(size, menu);
    b->boom = create_boom(menu);
    return b;
}

void reset_ballon(ballon_t *ballon, sfVector2u size)
{
    srand(time(NULL));
    ballon->d = rand() % 2;
    ballon->z = 5 + (double)rand() * 2 / RAND_MAX;
    ballon->y = (rand() % 486 - (40 * (ballon->z - 5)) + 120)\
    * (int)size.y / 1010;
    ballon->r = 100 + rand() % 156;
    ballon->g = 100 + rand() % 156;
    ballon->b = 100 + rand() % 156;
    ballon->anim = 0;
    ballon->x = -(16 * ballon->z + 81);
    ballon->x += ((int)size.x + 80 + -ballon->x) * ballon->d;
    sfSprite_setScale(ballon->sprite, (sfVector2f){ballon->z, ballon->z});
    sfClock_restart(ballon->clockanim);
    sfClock_restart(ballon->clockmove);
}

static void fail(ballon_t *ballon, sfRenderWindow *window)
{
    reset_ballon(ballon, sfRenderWindow_getSize(window));
    ballon->l->life--;
}

static void draw_ballon(sfRenderWindow *window, ballon_t *ballon)
{
    sfVector2u size = sfRenderWindow_getSize(window);
    sfIntRect area = {22 * ballon->anim, 0, 16, 40};
    sfColor color = {ballon->r, ballon->g, ballon->b, 255};

    sfSprite_setPosition(ballon->sprite\
    , (sfVector2f){ballon->x * 1920 / (int)size.x\
    , ballon->y * 1010 / (int)size.y});
    sfSprite_setColor(ballon->sprite, color);
    sfSprite_setTextureRect(ballon->sprite, area);
    sfRenderWindow_drawSprite(window, ballon->sprite, NULL);
}

void display_ballon(sfRenderWindow *window, ballon_t *ballon)
{
    sfVector2u size = sfRenderWindow_getSize(window);
    float timea = sfTime_asSeconds(sfClock_getElapsedTime(ballon->clockanim));
    float timem = sfTime_asSeconds(sfClock_getElapsedTime(ballon->clockmove));
    float time = 0.0025 / (1 + ((float)ballon->s->score / 50));

    draw_ballon(window, ballon);
    if (timea > 0.2) {
        sfClock_restart(ballon->clockanim);
        ballon->anim += (ballon->anim == 4) ? -4 : 1;
    }
    if (timem > time) {
        ballon->x += (ballon->d) ? -((float)size.x / 1920\
        ) * (timem / time) : ((float)size.x / 1920) * (timem / time);
        sfClock_restart(ballon->clockmove);
        if ((ballon->x < -16 * ballon->z - 1 && ballon->d)
        || (ballon->x > (int)size.x && !ballon->d))
            fail(ballon, window);
    }
}

void display_b(sfRenderWindow *window, all_b_t *b)
{
    if (b->boom->z > b->ballon->z) {
        display_boom(window, b->boom);
        display_ballon(window, b->ballon);
    } else {
        display_ballon(window, b->ballon);
        display_boom(window, b->boom);
    }
}
