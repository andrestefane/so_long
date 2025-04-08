/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 05:46:53 by astefane          #+#    #+#             */
/*   Updated: 2025/04/08 14:22:51 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_img(t_game *game)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./img/grass.png");
	game->img_background = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./img/tree.png");
	game->img_wall = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./img/diamante1.png");
	game->img_coin = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./img/cofre.png");
	game->img_exit = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./img/player.png");
	game->img_player = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
}

void	put_image(t_game *game, int i)
{
	int	pos_x;
	int	pos_y;

	pos_y = (i / game->width) * 64;
	pos_x = (i % game->width) * 64;
	mlx_image_to_window(game->mlx, game->img_background, pos_x, pos_y);
	if (game->big_line[i] == 'P')
		mlx_image_to_window(game->mlx, game->img_player, pos_x, pos_y);
	if (game->big_line[i] == 'C')
		mlx_image_to_window(game->mlx, game->img_coin, pos_x, pos_y);
	if (game->big_line[i] == '1')
		mlx_image_to_window(game->mlx, game->img_wall, pos_x, pos_y);
	if (game->big_line[i] == '0')
		mlx_image_to_window(game->mlx, game->img_background, pos_x, pos_y);
	if (game->big_line[i] == 'E')
		mlx_image_to_window(game->mlx, game->img_exit, pos_x, pos_y);
}

void	place(t_game *game)
{
	int	i;

	if (!game || !game->big_line)
		ft_error("Error in placing imagens", 0);
	i = 0;
	while (game->big_line[i])
	{
		if (game->big_line[i] == '\n')
		{
			i++;
			continue ;
		}
		put_image(game, i);
		i++;
	}
}

void	check_img(t_game *game)
{
	game->path_player = "./img/player.png";
	game->path_wall = "./img/tree.png";
	game->path_coin = "./img/diamante1.png";
	game->path_exit = "./img/cofre.png";
	game->path_back_ground = "./img/grass.png";
	game->fd_player = open(game->path_player, O_RDONLY);
	if (game->fd_player < 0)
		ft_error_and_free(game, " Error\n Loading imagenes\n", 1);
	game->fd_wall = open(game->path_wall, O_RDONLY);
	if (game->fd_wall < 0)
		ft_error_and_free(game, " Error\n Loading imagenes\n", 1);
	game->fd_coin = open(game->path_coin, O_RDONLY);
	if (game->fd_coin < 0)
		ft_error_and_free(game, " Error\n Loading imagenes\n", 1);
	game->fd_exit = open(game->path_exit, O_RDONLY);
	if (game->fd_exit < 0)
		ft_error_and_free(game, " Error\n Loading imagenes\n", 1);
	game->fd_back_ground = open(game->path_back_ground, O_RDONLY);
	if (game->fd_back_ground < 0)
		ft_error_and_free(game, " Error\n Loading imagenes\n", 1);
}
