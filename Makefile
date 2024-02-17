# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 16:47:21 by yoshimurahi       #+#    #+#              #
#    Updated: 2024/02/17 10:09:22 by cjia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -g
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address
CFLAGS += -fsanitize=thread
RM = rm -f
INCLUDES = -I./inc -I./srcs/
SRCS_DIR = srcs/
OBJS_DIR = objs/

SRCS = srcs/main.c srcs/init_main.c srcs/utils.c srcs/start_philo.c srcs/routine.c srcs/take_drop_forks.c srcs/monitor.c srcs/one_philo.c
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
