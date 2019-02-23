# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 18:40:55 by rreedy            #+#    #+#              #
#    Updated: 2019/02/22 18:23:26 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ls
LIB += libft/libft.a

OBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

CC := gcc
INCLUDES := -I./includes -I./libft/includes
CFLAGS += -Wall -Wextra -Werror $(INCLUDES)
LFLAGS += -L./libft -lft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(LIB):
	make -C libft

clean:
	@- $(RM) $(OBJS) 
	@- make -C libft clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C libft fclean

re: fclean all
