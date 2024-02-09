# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 15:42:18 by mohilali          #+#    #+#              #
#    Updated: 2024/02/09 19:05:45 by mohilali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = philo.c philo_utils.c philo_routine.c philo_helper.c \
		philo_monitor.c philo_create.c

SRB = ${SRC:.c=.o}

CC = cc 
CFALGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = philo
HEADER = philo.h

all: $(NAME)

$(NAME) : $(SRB)
	$(CC) $(SRB) -o $(NAME) -fsanitize=thread

%.o : %.c $(HEADER)
	$(CC) $(CFALGS) -c -pthread $< -o $@

clean :
	$(RM) $(SRB)

fclean : clean
	$(RM) $(NAME)

re :  fclean all