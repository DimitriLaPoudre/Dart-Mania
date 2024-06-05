/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** for my files
*/

#ifndef MY_H_
    #define MY_H_

    #include "linked_list.h"
    #include "garbage.h"
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stddef.h>
    #include <time.h>
    #include <math.h>

typedef struct framebuffer {
    unsigned char *pixels;
    unsigned int width;
    unsigned int height;
} framebuffer_t;

typedef struct score {
    sfSprite *sprite;
    sfText *text;
    char *text_score;
    int score;
    char *text_record;
    int record;
} score_t;

typedef struct life {
    sfSprite *sprite;
    int life;
    int anim;
    sfClock *clock;
} life_t;


typedef struct ballon {
    float x;
    float y;
    double z;
    short r;
    short g;
    short b;
    sfSprite *sprite;
    int anim;
    short d;
    sfClock *clockanim;
    sfClock *clockmove;
    score_t *s;
    life_t *l;
} ballon_t;

typedef struct boom {
    float x;
    float y;
    double z;
    short r;
    short g;
    short b;
    sfSprite *sprite;
    int anim;
    sfClock *clock;
    sfSound *pop;
} boom_t;

typedef struct all_b {
    ballon_t *ballon;
    boom_t *boom;
} all_b_t;

typedef struct cursor {
    sfSprite *sprite;
} cursor_t;

typedef struct eric {
    float x;
    float y;
    sfSprite *sprite;
    int d;
    sfSound *music;
} eric_t;

typedef struct button {
    float x[9];
    float y[9];
    sfSprite *sprite;
    int who[9];
    int state[9];
    sfClock *clock;
    sfSound *music[9];
    int action;
} button_t;

typedef struct menu {
    sfRenderWindow *window;
    sfSprite *sprite;
    eric_t *eric;
    sfMusic *music;
    cursor_t *cursor;
    sfVector2u size;
    int fps;
    float v_music;
    float v_fx;
    short slider;
    short mode;
} menu_t;

typedef struct pause {
    sfTexture *texture;
    sfSprite *sprite;
    button_t *button;
} pause_t;

typedef struct endgame {
    sfSprite *sprite;
    button_t *button;
    score_t *score;
} end_t;

typedef struct greyworld {
    sfTexture *texture;
    sfSprite *sprite;
} greyworld_t;

typedef struct dart {
    float x;
    float y;
    float z;
    short anim;
    sfSprite *sprite;
    short state;
    float dist;
    float mdist;
    float angle;
    sfClock *clockmove;
    short hit;
    sfSound *sound;
} dart_t;

void my_putchar(char c);

void my_putstr(char const *str);

void my_puterror(char const *str);

int my_miniprintf(char const *format, ...);

int my_strlen(char const *str);

long long my_getnbr(char *str);

long long my_power(long long nb, long long p);

long double my_power_float(long double nb, int p);

void my_putnbr(long long nb);

void my_putnbr_base(unsigned long long nb, char const *base);

char *my_stradd(char *src, char c);

char *my_strcpy(char *dest, char const *src);

char *my_strdup(char const *src);

char *my_strcat(char *dest, char const *src);

int my_strcmp(char const *s1, char const *s2);

void my_put_in_list(linked_list_t **list, char *data);

void my_rev_list(linked_list_t **begin);

int my_listlen(linked_list_t *begin);

int my_delete_node(linked_list_t **begin, void const *data_ref);

int my_delete_nodes(linked_list_t **begin, void const *data_ref);

//MY_HUNTER:

void help(void);

void menu(void);

score_t *my_hunter_wizard(menu_t *menu);

score_t *my_hunter_dart(menu_t *menu);

score_t *my_hunter_xtrem(menu_t *menu);

//MODE:

void choose_mode(menu_t *menu);

score_t *which_mode(menu_t *menu);

//BALLON:

all_b_t *create_b(sfVector2u size, menu_t *menu);

void display_b(sfRenderWindow *window, all_b_t *b);

ballon_t *create_ballon(sfVector2u size, menu_t *menu);

void reset_ballon(ballon_t *ballon, sfVector2u size);

void display_ballon(sfRenderWindow *window, ballon_t *ballon);

//BOOM:

boom_t *create_boom(menu_t *menu);

void reset_boom(boom_t *boom, ballon_t *ballon, menu_t *menu);

void display_boom(sfRenderWindow *window, boom_t *boom);

//CURSOR:

cursor_t *create_cursor(void);

void display_cursor(sfRenderWindow *window, cursor_t *cursor);

void get_position(float *x, float *y, sfRenderWindow *window);

//DART:

dart_t *create_dart(menu_t *menu);

void display_dart(menu_t *menu, dart_t *dart, all_b_t *b);

void check_events_dart(sfEvent event, all_b_t *b, dart_t *dart, menu_t *menu);

void display_order(menu_t *menu, dart_t *dart, all_b_t *b);

//ERIC:

eric_t *create_eric(sfVector2u size, menu_t *menu);

void eric_shot(sfVector2u size, sfMouseButtonEvent mouse, menu_t *menu);

void eric_leave(menu_t *menu, int d);

int salut_chef(sfSound *music, menu_t *menu);

//MENU:

button_t *menu_button(menu_t *menu);

void display_button(sfRenderWindow *window, button_t *button, int nb);

void go_play(menu_t *menu);

void display_score(sfRenderWindow *window, score_t *s);

void display_hud(sfRenderWindow *window, score_t *s, life_t *l);

void check_events(sfEvent event\
    , all_b_t *b, menu_t *menu);

//ENDGAME:

button_t *endgame_button(menu_t *menu);

void gameover(menu_t *menu, score_t *s);

greyworld_t *get_greyend(menu_t *menu, score_t *s, end_t *eg);

//PAUSE:

void menu_pause(all_b_t *b, menu_t *menu, dart_t *dart);

button_t *pause_button(menu_t *menu);

void grey_world(sfRenderWindow *window, sfSprite *sprite);

//SETTING:

void setting(menu_t *menu, all_b_t *b, sfSprite *bg);

button_t *setting_quit(menu_t *menu);


void destroyer(sfRenderWindow *window, sfClock *clock, sfMusic *music);

#endif /* MY_H_ */
