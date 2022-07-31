##
## EPITECH PROJECT, 2022
## nmobjdump
## File description:
## Makefile
##

UNAME := $(shell uname)

SRC_DIR	=	src/

EXEC_DIR	=	execs/

SRC		=	$(SRC_DIR)main.c \
			$(SRC_DIR)process.c \
			$(SRC_DIR)$(EXEC_DIR)exec_base.c \
			$(SRC_DIR)$(EXEC_DIR)exec_dir.c \
			$(SRC_DIR)$(EXEC_DIR)exec_files.c \
			$(SRC_DIR)$(EXEC_DIR)exec_help.c \
			$(SRC_DIR)$(EXEC_DIR)exec_others.c \
			$(SRC_DIR)check_args.c \
			$(SRC_DIR)exec_command.c \
			$(SRC_DIR)handle_exec.c \
			$(SRC_DIR)handle_client.c \
			$(SRC_DIR)handle_clients_nodes.c \
			$(SRC_DIR)main_loop.c \

SRC_T 		=	$(shell find ./lib/my -name "*.c") \
				$(SRC_DIR)$(EXEC_DIR)exec_base.c \
				$(SRC_DIR)check_args.c \


TEST_FILES 	=	$(shell find ./tests -name "*.c") \
				$(shell find ./lib/tests -name "*.c") \

NAME	=	myftp

TEST_N		=	unit_tests

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-I./include -I./lib/my -W -Wall -Wextra -Wshadow -std=gnu11

T_FLAGS	=	-I./lib/my -I./include -lcriterion --coverage

ifeq ($(UNAME), Darwin)
	T_FLAGS += -I/opt/homebrew/include  -L/opt/homebrew/lib
endif

LDFLAGS	=	-L./lib/my -lmy

CC		=	gcc

all:		$(NAME)

$(NAME):	$(OBJ)
			$(MAKE) -C ./lib/my/
			$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LDFLAGS)

tests_run:
			$(CC) -o $(TEST_N) $(TEST_FILES) $(SRC_T) $(T_FLAGS)
			./unit_tests --verbose
			gcovr --exclude-throw-branches --exclude-unreachable-branches -e lib/tests/ -e tests/ -e $(SRC_DIR)main.c -b

clean:
			@find ./ -type f -name '*.o' -delete
			@find ./ -type f -name '*.gcda' -delete
			@find ./ -type f -name '*.gcno' -delete
			@find ./ -type f -name 'vgcore.*' -delete
			make clean -C ./lib/my

fclean:		clean
			rm -f $(NAME)
			rm -f $(TEST_N)
			make fclean -C ./lib/my

re:			fclean all

debug: 		CFLAGS += -g
debug: 		re

.PHONY: 	all clean fclean re debug
