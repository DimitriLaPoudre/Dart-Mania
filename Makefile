##
## EPITECH PROJECT, 2023
## bs_my_ls
## File description:
## Makefile
##

NAME = Dart_Mania

SRC = src/hub.c \
	  src/menu.c \
	  src/mode.c \
	  src/transition_to_hunter.c \
      src/my_hunter.c \
	  src/menu_pause.c \
	  src/setting.c \
      src/help.c \
	  lib/hunter/analise_events.c \
	  lib/hunter/analise_events_dart.c \
	  lib/hunter/use_ballon.c \
	  lib/hunter/use_boom.c \
	  lib/hunter/cursor.c \
	  lib/hunter/dart.c \
	  lib/hunter/use_hud.c \
	  lib/hunter/use_eric.c \
	  lib/hunter/use_button.c \
	  lib/hunter/destroyer.c

OBJ = $(SRC:.c=.o)

CFLAGS = -I.include/ -L./lib/my/ -lmy -L./lib/garbage/ -lgarbage -l\
csfml-graphics -l csfml-system -l csfml-audio -l m -g3

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib/my/
	make -C lib/garbage/
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -rf $(OBJ)
	make -C lib/my/ clean
	make -C lib/garbage/ clean

fclean: clean
	rm -rf $(NAME)
	make -C lib/my/ fclean
	make -C lib/garbage/ fclean

re: fclean all
