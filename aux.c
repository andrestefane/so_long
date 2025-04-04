/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:17:55 by astefane          #+#    #+#             */
/*   Updated: 2025/04/02 19:11:16 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_big_line(char **big_line)
{
	char	**ptr;

	ptr = big_line;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(big_line);
}

void	free_game(t_game *game)
{
	if (game->big_line)
		free(game->big_line);
	free(game);
}

void	parsing(t_game *game, char *map)
{
	check_map_name(map);
	reading_map(game, map);
	check_map(game);
	game->mlx = mlx_init(game->width * 64, game->heigh * 64, "so_long", false);
	if (!game->mlx)
	{
		ft_putstr("Error: Failed to initialize mlx\n");
		free_game(game);
		exit(1);
	}
	load_img(game);
	place(game);
	mlx_key_hook(game->mlx, &key_press, game);
	mlx_loop(game->mlx);
	destroy_imagen(game);
	mlx_terminate(game->mlx);
	free_game(game);
	exit (0);
}
