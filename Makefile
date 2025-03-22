# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astefane <astefane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/22 15:47:58 by astefane          #+#    #+#              #
#    Updated: 2025/03/22 17:51:47 by astefane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBFT = libft
LIBFT_DIR = libft/
MINILIB = libmlx
MINILIB_DIR = minilib/
MINILIB_LIB = $(MINILIB_DIR)libmlx.a
LIBFT_LIB = $(LIBFT_DIR)libft.a

SRCS = \
		so_long.c \

OBJS = $(SRCS:.c=.o)
NAME = so_long

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MINILIB_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_LIB) $(MINILIB_LIB) -lXext -lX11 -lm -lbsd

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(MINILIB_LIB):
	make -C $(MINILIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINILIB_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(MINILIB_DIR)

re: fclean all

.PHONY: all clean fclean re