##
## EPITECH PROJECT, 2022
## nmobjdump
## File description:
## Makefile
##

SRC	=	$(shell find ./ -name "*.c")

NAME	=	libmy.a

OBJ	= 	$(SRC:.c=.o)

CC	= 	gcc

CFLAGS	=	-Wall -Wshadow -Wextra -I../../include/

RM	=	rm

all:	$(NAME)

$(NAME):	$(OBJ)
	@echo "\033[0;33mCOMPILING LIB\033[0m"
	$(AR) rc $(NAME) $(OBJ)
	@echo "\033[0;32mLIB COMPILED\033[0m"

clean:
	$(RM) -rf $(OBJ)

fclean:	clean
	$(RM) -rf $(NAME)

re: fclean all

.PHONY = re fclean clean $(NAME) all
