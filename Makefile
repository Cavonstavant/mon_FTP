##
## EPITECH PROJECT, 2022
## B-PSU-400-NAN-4-1-malloc-constant.vigneron
## File description:
## Makefile
##

NAME := myftp

$(NAME):
	cmake .
	make

clean:
	cmake . && make clean

fclean:
	cmake . && make fclean

re:
	cmake . && make re

all:
	cmake . && make

.PHONY: all clean fclean re