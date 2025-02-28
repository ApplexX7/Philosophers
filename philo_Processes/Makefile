# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 12:48:24 by mohilali          #+#    #+#              #
#    Updated: 2025/02/28 15:26:36 by mohilali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = philo.c philo_utils.c philo_time.c philo_checking.c \
		philo_fork.c philo_routine.c \

OBJCT = ${SRC:.c=.o}
CC = cc 
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
NAME = philo
HEADER_NAME = philo.h

all : $(NAME)

$(NAME) : $(OBJCT)
	$(CC) $(OBJCT) -pthread -o $(NAME)

%.o : %.c $(HEADER_NAME)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJCT)

fclean : clean
	$(RM) $(NAME)

re : fclean all