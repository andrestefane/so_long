/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:57:44 by astefane          #+#    #+#             */
/*   Updated: 2025/03/22 20:55:09 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_destroy_window(game->mlx, game->window);
	ft_putstr("Game Closed\n");
	exit(0);
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx, game->window);
		ft_putstr("Game Closed\n");
		exit(0);
	}
	return (0);
}

void	check_map(char *map)
{
	int	i;

	i = ft_strlen(map);
	if (i <= 4 || ft_strncmp(map + i - 4, ".ber", 4) != 0)
		ft_error(".ber not found", 0);
}

void	init_data(t_game game, char *map)
{
	game.moves = 0;
	check_map(map);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){0};
	if (argc != 2)
		ft_error("Error with arguments\n", 0);
	init_data(game, argv[1]);
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 800, 600, "So_long");
	mlx_hook(game.window, 17, 0L, close_window, &game);
	mlx_hook(game.window, 2, 1L << 0, (int (*)
			(int, void *)) handle_key, &game);
	mlx_loop(game.mlx);
	mlx_destroy_window(game.mlx, game.window);
	return (0);
}
