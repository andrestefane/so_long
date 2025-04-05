/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:57:44 by astefane          #+#    #+#             */
/*   Updated: 2025/04/02 18:56:40 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error_and_free(t_game *game, char *str_error, int exit)
{
	if (game->big_line)
		free(game->big_line);
	free(game);
	ft_error(str_error, exit);
}

void	key_press(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	if (keydata.action == MLX_RELEASE)
		return ;
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(game->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_W)
		ft_up(game);
	if (keydata.key == MLX_KEY_D)
		ft_right(game);
	if (keydata.key == MLX_KEY_A)
		ft_left(game);
	if (keydata.key == MLX_KEY_S)
		ft_down(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("Memorry allocted failed", 1);
	*game = (t_game){0};
	if (argc != 2)
		ft_error("Error with arguments\n", 0);
	parsing(game, argv[1]);
	return (0);
}
