# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 18:40:55 by rreedy            #+#    #+#              #
#    Updated: 2019/01/08 16:35:55 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ls
LIB += libftprintf/libftprintf.a

OBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

CFLAGS += -g -Wall -Wextra -Werror -I./includes -I./libftprintf/includes
LFLAGS += -L./libftprintf -lftprintf

.PHONY: all clean fclean re

all: $(LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

clean:
	@- $(RM) $(OBJS) 

fclean: clean
	@- $(RM) $(NAME)

re: fclean all
