# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 11:14:15 by mchaya            #+#    #+#              #
#    Updated: 2021/05/16 11:39:13 by mchaya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c utils.c utils1.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) philo_one.h
	gcc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	-rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean re
