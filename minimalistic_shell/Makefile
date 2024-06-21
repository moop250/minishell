all: *.c *.h
	make -C libft
	gcc -Wall -Wextra -Werror -std=c99 *.c -lreadline -L libft -lft

clean:
	rm -f a.out
	make -C libft fclean

:PHONY: all clean