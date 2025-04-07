/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:02:39 by astefane          #+#    #+#             */
/*   Updated: 2025/04/07 20:12:29 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "./ft_libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include "./MLX42/include/MLX42/MLX42_Int.h"

typedef struct game
{
	void	*mlx;
	void	*start;
	void	*img_wall;
	void	*img_player;
	void	*img_coin;
	void	*img_exit;
	void	*img_background;
	int		moves;
	int		errors;
	int		x;
	int		y;
	int		heigh;
	int		width;
	char	*big_line;
	int		wall;
	int		exit;
	int		player;
	int		background;
	int		coins;
	int		copy_coins;
	int		fd_player;
	int		fd_wall;
	int		fd_coin;
	int		fd_exit;
	int		fd_back_ground;
	char	*path_player;
	char	*path_wall;
	char	*path_coin;
	char	*path_exit;
	char	*path_back_ground;
	int		size_heigh;
	int		size_width;

}	t_game;

// Funciones de parseo para comprobar el mapa

void	process_map_lines(t_game *game, int fd, char **temp_big_line);
void	check_map_name(t_game *game, char *map);
void	reading_map(t_game *game, char	*map);
void	ft_check_obligatory(t_game *game);
void	ft_check_top_bot(t_game *game);
void	ft_check_side(t_game *game);

//Funciones para cargar imagenes

void	place(t_game *game);
void	put_image(t_game *game, int i);
void	load_img(t_game *game);

//Parseo dup_map

void	check_map(t_game *game);
void	ft_flood_flip(t_game *game, int x, char *map);
int		is_exit_reachable(t_game *game, char *map);
int		ft_find_player(char *big_line);

//Aux

void	check_img(t_game *game);
void	free_game(t_game *game);
void	parsing(t_game *game, char *map);
void	check_len(t_game *game);
void	ft_error_and_free(t_game *game, char *str_error, int exit);

//moves

void	key_press(mlx_key_data_t keydata, void *param);
void	ft_up(t_game *game);
void	ft_left(t_game *game);
void	ft_down(t_game *game);
void	ft_right(t_game *game);
void	destroy_imagen(t_game *game);
int		check_exit(t_game *game, char c);

#endif