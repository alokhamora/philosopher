# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/10 14:40:17 by mchaya            #+#    #+#              #
#    Updated: 2021/05/10 15:12:18 by mchaya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c utils.c utils1.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean re