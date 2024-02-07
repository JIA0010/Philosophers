# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 16:47:21 by yoshimurahi       #+#    #+#              #
#    Updated: 2024/02/07 12:58:22 by yoshimurahi      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -g
# CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INCLUDES = -I./inc -I./srcs/
SRCS_DIR = srcs/
OBJS_DIR = objs/

SRCS = srcs/main.c srcs/init_main.c srcs/utils.c srcs/start_philo.c srcs/routine.c srcs/take_drop_forks.c
OBJS		=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

all: $(NAME)
$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re