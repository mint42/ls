# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 18:40:55 by rreedy            #+#    #+#              #
#    Updated: 2019/09/04 16:45:20 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ls
LIB += libft/libft.a

OBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

CC := gcc
INCLUDES := -I./includes -I./libft/includes -I./libft/includes/ft_printf
CFLAGS += -g -Wall -Wextra -Werror $(INCLUDES)
LFLAGS += -L./libft -lft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(LIB):
	@- make -C libft/ all

clean:
	@- $(RM) $(OBJS) 
	@- make -C libft/ clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C libft/ fclean

re: fclean all

install: $(NAME)
	ln -sv $(shell pwd)/$(NAME) ~/bin/ft_ls
