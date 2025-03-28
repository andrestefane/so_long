# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astefane <astefane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/22 15:47:58 by astefane          #+#    #+#              #
#    Updated: 2025/03/28 08:18:49 by astefane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

LIBFT = libft
LIBFT_DIR = ft_libft/
MINILIB_DIR = MLX42
MINILIB_BUILD_DIR = $(MINILIB_DIR)/build
MINILIB_LIB = $(MINILIB_BUILD_DIR)/libmlx42.a
LIBFT_LIB = $(LIBFT_DIR)libft.a
MLX42_INC_DIR = MLX42/include

MLX42_REPO = https://github.com/codam-coding-college/MLX42.git

SRCS = \
    so_long.c \
	aux.c \
    read_map/reading_map.c \
	load_map/load_map.c \
	parsing_matriz/parsing.c 

OBJS = $(SRCS:.c=.o)
NAME = so_long

INCLUDES = -I includes -I$(MLX42_INC_DIR)
CFLAGS += $(INCLUDES)

LDFLAGS = -L$(MINILIB_BUILD_DIR) -lmlx42 -lglfw -lXext -lX11 -lm -lbsd -no-pie

all: $(MINILIB_LIB) $(LIBFT_LIB) $(NAME)

$(MINILIB_DIR):
	git clone $(MLX42_REPO)

$(MINILIB_LIB): $(MINILIB_DIR)
	mkdir -p $(MINILIB_BUILD_DIR)
	cd $(MINILIB_BUILD_DIR) && cmake .. && make

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MINILIB_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_LIB) $(MINILIB_LIB) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_DIR)
	@if [ -d "$(MINILIB_BUILD_DIR)" ]; then make clean -C $(MINILIB_BUILD_DIR); fi

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)
	@if [ -d "$(MINILIB_DIR)" ]; then rm -rf $(MINILIB_DIR); fi
	rm -rf $(MINILIB_BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re $(MINILIB_DIR)
