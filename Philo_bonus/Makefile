# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 12:48:24 by mohilali          #+#    #+#              #
#    Updated: 2024/02/12 12:18:24 by mohilali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = philo_bonus.c philo_bonus_utils.c philo_bonus_time.c philo_bonus_checking.c \
	philo_bonus_fork.c philo_bonus_routine.c

OBJCT = ${SRC:.c=.o}
CC = cc 
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
NAME = philo_bonus
HEADER_NAME = philos_bonus.c

all : $(NAME)

$(NAME) : $(OBJCT)
	$(CC) $(OBJCT) -o $(NAME)

%.o : %.c $(HEADER_NAME)
	$(CC)  -c $^ -o $@

clean :
	$(RM) $(OBJCT)

fclean : clean
	$(RM) $(NAME)

re : fclean all