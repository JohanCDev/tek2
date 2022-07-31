##
## EPITECH PROJECT, 2022
## 205IQ
## File description:
## Makefile
##

NAME	= 	205IQ

SRC		=	./205iq.py

SRC_T	=	./tests.py

TESTS_NAME	=	./unit_tests.py

CP		=	cp

CHMOD	=	chmod

EXEC_RIGHTS	=	+x

RM		=	rm -rf

all: $(NAME)

$(NAME):
	$(CP) $(SRC) ./$(NAME)
	$(CHMOD) $(EXEC_RIGHTS) $(NAME)

tests_run: all
	$(CP) $(SRC_T) $(TESTS_NAME)
	$(CHMOD) $(EXEC_RIGHTS) $(TESTS_NAME)
	pytest --cov=process --cov=results --cov=main $(TESTS_NAME)

clean:
	$(RM) $(TESTS_NAME)
	$(RM) .coverage
	$(RM) .pytest_cache/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re