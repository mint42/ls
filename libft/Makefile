# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 14:31:20 by rreedy            #+#    #+#              #
#    Updated: 2019/02/20 13:57:44 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

POBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/ft_printf/*.c))
LOBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

CFLAGS += -Wall -Wextra -Werror -I./includes
LFLAGS += -L./ -lft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(POBJS) $(LOBJS)
	ar rc $(NAME) $(POBJS) $(LOBJS)
	ranlib $(NAME)

test: all main.o
	$(CC) $(CFLAGS) main.o $(LFLAGS)

clean:
	@- $(RM) $(LOBJS) $(POBJS) a.out main.o

fclean: clean
	@- $(RM) $(NAME)

re: fclean all
