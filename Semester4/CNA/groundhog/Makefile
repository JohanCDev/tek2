##
## EPITECH PROJECT, 2022
## nmobjdump
## File description:
## Makefile
##

NAME	=	groundhog

SRC_F	=	./groundhog.py

SRC_T	=	./tests.py

TESTS_NAME	=	unit_tests.py

CP		=	cp

CHMOD	=	chmod

EXEC	=	+x

RM		=	rm -rf

all:
	$(CP) $(SRC_F) $(NAME)
	$(CHMOD) $(EXEC) $(NAME)
	@echo "\033[0;32mProject built\033[0m"

tests_run: all
	$(CP) $(SRC_T) $(TESTS_NAME)
	$(CHMOD) $(EXEC) $(TESTS_NAME)
	pytest --cov=process --cov=calculation --cov=groundhog $(TESTS_NAME)
	./test_output.sh

clean:
	$(RM) $(TESTS_NAME)
	$(RM) .coverage
	$(RM) .pytest_cache/
	$(RM) ./tests_files/our_out
	@echo "\033[0;32mTests binary cleaned\033[0m"

fclean:		clean
	$(RM) $(NAME)
	@echo "\033[0;32mEverything has been cleaned\033[0m"



re:			fclean all

.PHONY: all clean fclean re
