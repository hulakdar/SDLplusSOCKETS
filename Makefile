# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/14 17:43:47 by ftymchyn          #+#    #+#              #
#    Updated: 2018/03/15 14:38:53 by skamoza          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER   = server
CLIENT   = client
CC	     = clang
FLAGS    = -c -g
SRCS     = server.c client.c
OBJS	 = $(SRCS:%.c=%.o)
INCL	 = -I /Library/Frameworks/SDL2.framework/Headers
LIBS	 = -L. /Library/Frameworks/SDL2.framework/SDL2


all : $(SERVER) $(CLIENT)

$(SERVER) : server.o
	@$(CC) server.o $(LIBS) -o $@
	@echo "$@ successful build"

$(CLIENT) : main.o
	@$(CC) main.o $(LIBS) -o $@
	@echo "$@ successful build"

%.o : %.c
	@$(CC) $(INCL) $(FLAGS) $< -o $@

clean :
	@rm -f *.o

fclean: clean
	@rm -f $(SERVER) $(CLIENT)

re: fclean all
