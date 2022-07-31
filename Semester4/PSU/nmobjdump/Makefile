##
## EPITECH PROJECT, 2022
## nmobjdump
## File description:
## Makefile
##

NM_DIR	=	nmdir/

OBJDUMP_DIR	=	objdumpdir/

SRC_DIR	=	src/

SRC_NM	=	$(shell find ./$(NM_DIR)$(SRC_DIR) -name "*.c")

SRC_OBJDUMP	=	$(shell find ./$(OBJDUMP_DIR)$(SRC_DIR) -name "*.c")

NAME_NM	=	nm

NAME_OBJDUMP=	objdump

OBJ_NM	=	$(SRC_NM:.c=.o)

OBJ_OBJDUMP	=	$(SRC_OBJDUMP:.c=.o)

CFLAGS	=	-I./include -I./lib/my -W -Wall -Wextra -Wshadow -std=gnu11

LDFLAGS	=	-L./lib/my -lmy

CC	=	gcc

all:		$(NAME_NM) $(NAME_OBJDUMP)

$(NAME_NM):	$(OBJ_NM)
			$(MAKE) -C ./lib/my
			$(CC) -o my_$(NAME_NM) $(OBJ_NM) $(LDFLAGS)

$(NAME_OBJDUMP):	$(OBJ_OBJDUMP)
			$(MAKE) -C ./lib/my
			$(CC) -o my_$(NAME_OBJDUMP) $(OBJ_OBJDUMP) $(LDFLAGS)

clean:
			@find ./ -type f -name '*.o' -delete
			@find ./ -type f -name '*.gcda' -delete
			@find ./ -type f -name '*.gcno' -delete
			@find ./ -type f -name 'vgcore.*' -delete
			$(MAKE) clean -C ./lib/my

fclean:		clean
			$(MAKE) fclean -C ./lib/my
			rm -f my_$(NAME_NM)
			rm -f my_$(NAME_OBJDUMP)


re:			fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
