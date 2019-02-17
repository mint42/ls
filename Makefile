# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 18:40:55 by rreedy            #+#    #+#              #
#    Updated: 2019/02/16 18:16:13 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ls
LIB += libftprintf/libftprintf.a

OBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

INCLUDES := -I./includes -I./libftprintf/includes
CFLAGS += -Wall -Wextra -Werror $(INCLUDES)
LFLAGS += -L./libftprintf -lftprintf

.PHONY: all clean fclean re

all: $(LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(LIB):
	make -C libftprintf

clean:
	@- $(RM) $(OBJS) 
	@- make -C libftprintf clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C libftprintf fclean

re: fclean all
