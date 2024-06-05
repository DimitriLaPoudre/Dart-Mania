##
## EPITECH PROJECT, 2023
## Makefile_my
## File description:
## Makefiile for mylib
##

NAME = libgarbage.a

SRC = alloc.c \
	  alloc_sound.c \
	  alloc_sprite.c \
	  alloc_clock.c

OBJ = $(SRC:.c=.o)

all: libgarbage.a

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
