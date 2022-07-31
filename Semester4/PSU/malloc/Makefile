##
## EPITECH PROJECT, 2021
## Duo-7
## File description:
## Makefile
##

SRC_DIR		=	src/

SRC			=	$(shell find ./src -name "*.c") \

NAME		=	libmy_malloc.so

OBJ			=	$(SRC:.c=.o)

CFLAGS		=	-I./include -W -Wall -Wextra -Wshadow -std=gnu11 -fPIC

LDFLAGS		=	-shared

CC			=	gcc

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			@find ./ -type f -name '*.o' -delete
			@find ./ -type f -name '*.gcda' -delete
			@find ./ -type f -name '*.gcno' -delete
			@find ./ -type f -name 'vgcore.*' -delete

fclean:		clean
			rm -f $(NAME)


re:			fclean all

debug: 		CFLAGS += -g
debug: 		re

.PHONY: 	all clean fclean re debug
