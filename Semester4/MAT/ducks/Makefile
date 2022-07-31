##
## EPITECH PROJECT, 2022
## 204ducks
## File description:
## Makefile
##

NAME	= 	204ducks

CP		=	cp

CHMOD	=	chmod

EXEC_RIGHTS	=	+x

all: $(NAME)

$(NAME):
	$(CP) main.py ./$(NAME)
	$(CHMOD) $(EXEC_RIGHTS) $(NAME)

clean:
	@echo "\033[0;31mNothing to clean\033[0m"

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re