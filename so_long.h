/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:02:39 by astefane          #+#    #+#             */
/*   Updated: 2025/03/28 08:50:45 by astefane         ###   ########.fr       */
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
	void	*window;
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
	char	**map2d;
	char	*big_line;
	int		wall;
	int		exit;
	int		player;
	int		background;
	int		coins;
	int		count_line;
	int		key;

}	t_game;

// Funciones de parseo para comprobar el mapa

void	check_map_name(char *map);
void	ft_check_side(t_game *game);
void	ft_check_top_bot(t_game *game);
void	ft_check_obligatory(t_game *game);
void	reading_map(t_game *game, char	*map);
void	Check_map_limits(char *line, t_game *game);

//Funciones para cargar imagenes

void	place(t_game *game);
void	put_image(t_game *game, int i);
void	load_img(t_game *game);

//Parseo dup_map

void	check_dup_map(t_game *game);
void	allocate_map2d(t_game *game, char **dup_big_line);
void	ft_flood_flip(t_game *game, int y, int x, char **map);
int		check_matriz(t_game *game);
void	copy_to_map2d(t_game *game, char **dup_big_line);

//Aux

void	free_dup_big_line(char **dup_big_line);
void	print_map(t_game *game);
void	parsing(t_game *game, char *map);

void	key_press(mlx_key_data_t keydata, void *param);
void	ft_up(t_game *game);
void	ft_left(t_game *game);
void	ft_down(t_game *game);
void	ft_right(t_game *game);


#endif