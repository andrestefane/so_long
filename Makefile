# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astefane <astefane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/22 15:47:58 by astefane          #+#    #+#              #
#    Updated: 2025/04/02 11:54:30 by astefane         ###   ########.fr        #
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
    moves/moves.c \
    parsing_matriz/parsing.c 

OBJS = $(SRCS:.c=.o)
NAME = so_long

INCLUDES = -I includes -I$(MLX42_INC_DIR)
CFLAGS += $(INCLUDES)

LDFLAGS = -L$(MINILIB_BUILD_DIR) -lmlx42 -lglfw -lXext -lX11 -lm -lbsd -no-pie

TOTAL_FILES := $(words $(SRCS))
COUNT = 0

all: check_mlx $(LIBFT_LIB) $(NAME)

check_mlx:
	@if [ ! -d "$(MINILIB_DIR)" ]; then \
		echo "MLX42 no encontrado. Clonando y compilando..."; \
		git clone $(MLX42_REPO) $(MINILIB_DIR); \
		mkdir -p $(MINILIB_BUILD_DIR); \
		cd $(MINILIB_BUILD_DIR) && cmake .. && make; \
	else \
		echo "MLX42 ya existe. Omitiendo clonación y compilación."; \
	fi

$(LIBFT_LIB):
	@echo "\033[1;33mCompiling libft...\033[0m"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJS) $(LIBFT_LIB)
	@echo "	\033[38;5;51mReady to play the game\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_LIB) $(LDFLAGS)

%.o: %.c
	@if [ "$(COUNT)" -eq "0" ]; then echo "\033[1;33mCompiling So_long...\033[0m"; fi
	$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	$(eval PERCENT=$(shell echo $$(( $(COUNT) * 100 / $(TOTAL_FILES) ))))
	@echo "\033[1;32m[ $(PERCENT)%] Building C object $@\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;33mCleaning all .o files...\033[0m"
	@rm -rf $(OBJS) > /dev/null 2>&1
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1
	@if [ -d "$(MINILIB_BUILD_DIR)" ]; then \
		make clean -C $(MINILIB_BUILD_DIR) > /dev/null 2>&1; \
	fi

fclean: clean
	@rm -rf $(NAME) > /dev/null 2>&1
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1
	@if [ -d "$(MINILIB_DIR)" ]; then rm -rf $(MINILIB_DIR) > /dev/null 2>&1; fi
	@rm -rf $(MINILIB_BUILD_DIR) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re check_mlx
