# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/14 17:43:47 by ftymchyn          #+#    #+#              #
#    Updated: 2018/03/14 17:43:48 by ftymchyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = simple_SDL
CC	     = clang
FLAGS    = -Wall -Wextra -Werror -c
SRCS     = main.c
OBJS	 = $(SRCS:%.c=%.o)
INCL	 = -I /Library/Frameworks/SDL2.framework/Headers
LIBS	 = -L. /Library/Frameworks/SDL2.framework/SDL2

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(NAME) successful build"

%.o : %.c
	@$(CC) $(INCL) $(FLAGS) $< -o $@

clean :
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) $@ done"

re: fclean all