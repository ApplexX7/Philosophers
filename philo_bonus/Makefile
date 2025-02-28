# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 12:48:24 by mohilali          #+#    #+#              #
#    Updated: 2024/02/13 08:35:20 by mohilali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = philo_bonus.c philo_bonus_utils.c philo_bonus_time.c philo_bonus_checking.c \
		philo_bonus_fork.c philo_bonus_routine.c \

OBJCT = ${SRC:.c=.o}
CC = cc 
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
NAME = philo_bonus
HEADER_NAME = philo_bonus.h

all : $(NAME)

$(NAME) : $(OBJCT)
	$(CC) $(OBJCT) -pthread -o $(NAME) -fsanitize=thread

%.o : %.c $(HEADER_NAME)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJCT)

fclean : clean
	$(RM) $(NAME)

re : fclean all