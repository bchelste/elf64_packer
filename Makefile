# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:10:42 by bchelste          #+#    #+#              #
#    Updated: 2023/05/18 20:04:21 by bchelste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	woody_woodpacker
INC_DIR		=	includes
SRC_DIR		=	sources
CC			=	clang

SRCS		=	$(SRC_DIR)/main.c

OBJS		=	$(SRCS:.c=.o)

INC			=	-I$(INC_DIR)

HEAD		=	$(INC_DIR)/woody.h

CFLAGS		=	-Wextra -Werror -Wall $(INC)

OPTFLAGS	=	-O0

MAKE		=	make

RM			=	rm -rf

%.o:%.c $(HEAD)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

.PHONY: all clean fclean re hello

all:
	@$(MAKE) $(NAME) -j 4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean 
	$(RM) $(NAME)
	$(RM) hello

re: fclean all

hello:
	clang -m64 -o hello ./test_files/hello.c