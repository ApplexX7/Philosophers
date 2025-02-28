# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 15:42:18 by mohilali          #+#    #+#              #
#    Updated: 2024/02/16 17:32:36 by mohilali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = philo.c philo_time.c philo_utils.c philo_routine.c philo_create.c philo_help.c \
	philo_monitoring.c \

SRB = ${SRC:.c=.o}

CC = cc 
CFALGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = philo
HEADER = philo.h

all: $(NAME)

$(NAME) : $(SRB)
	$(CC) $(SRB) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFALGS) -pthread -c $< -o $@

clean :
	$(RM) $(SRB)

fclean : clean
	$(RM) $(NAME)

re :  fclean all