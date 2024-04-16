# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 15:13:08 by hlibine           #+#    #+#              #
#    Updated: 2024/04/16 17:17:54 by hlibine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

GREEN = \033[0;32m
ORANGE = \033[38;5;208m
RESET = \033[0m

FILES = srcs/ft_atoi \
			srcs/ft_bzero \
			srcs/ft_calloc \
			srcs/ft_isalnum \
			srcs/ft_isalpha \
			srcs/ft_isascii \
			srcs/ft_isdigit \
			srcs/ft_isprint \
			srcs/ft_itoa \
			srcs/ft_memchr \
			srcs/ft_memcmp \
			srcs/ft_memcpy \
			srcs/ft_memmove \
			srcs/ft_memset \
			srcs/ft_putchar_fd \
			srcs/ft_putendl_fd \
			srcs/ft_putnbr_fd \
			srcs/ft_putstr_fd \
			srcs/ft_split \
			srcs/ft_strchr \
			srcs/ft_strdup \
			srcs/ft_striteri \
			srcs/ft_strjoin \
			srcs/ft_strlcat \
			srcs/ft_strlcpy \
			srcs/ft_strlen \
			srcs/ft_strmapi \
			srcs/ft_strncmp \
			srcs/ft_strnstr \
			srcs/ft_strrchr \
			srcs/ft_strtrim \
			srcs/ft_substr \
			srcs/ft_tolower \
			srcs/ft_toupper \
			srcs/ft_realloc \
			srcs/ft_3dfree \
			srcs/garbage_collecter \
			srcs/garbage_collector_utils \
			srcs/ft_lstnew \
			srcs/ft_lstadd_front \
			srcs/ft_lstsize \
			srcs/ft_lstlast \
			srcs/ft_lstadd_back \
			srcs/ft_lstdelone \
			srcs/ft_lstclear \
			srcs/ft_lstiter \
			srcs/ft_lstmap \
			srcs/get_next_line/get_next_line \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = ${SRCS:.c=.o}

%.o: %.c
	@echo "\033[2K\rCompiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(AR) $@ $^

clean:
	@echo "$(ORANGE)extended_ft clean up...$(RESET)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "$(ORANGE)extended_ft full clean up...$(RESET)"
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re