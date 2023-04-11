# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: radaoudi <radaoudi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 17:34:49 by rania             #+#    #+#              #
#    Updated: 2023/04/11 15:06:19 by radaoudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	= srcs
SRCS_NAME	= main.c \
				check_arg.c \
				utils.c \
				init.c \
				time.c \
				routine.c \

OBJS_DIR	= objs
OBJS_NAME	= ${SRCS_NAME:.c=.o}
SRCS		= $(addprefix $(SRCS_DIR)/,$(SRCS_NAME))
OBJS		= $(addprefix $(OBJS_DIR)/,$(OBJS_NAME))
INC			= -I ./includes

NAME	= philo

CC		= gcc
RM		= rm -f
CFLAGS	= $(INC) -Wall -Wextra -Werror -pthread

# -fsanitize=address -g3
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
			@mkdir $(OBJS_DIR) 2> /dev/null || true
			$(CC) $(CFLAGS) -o $@ -c $<

clean:
			@rm -rf $(OBJS) $(OBJS_DIR)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
