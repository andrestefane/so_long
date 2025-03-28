/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:57:44 by astefane          #+#    #+#             */
/*   Updated: 2025/03/28 08:53:32 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void print_map(t_game *game)
{
    int y = 0;
    int x = 0;

    while (y < game->heigh)
    {
        x = 0;
        while (x < game->width)
        {
            printf("%c", game->map2d[y][x]);
            x++;
        }
        printf("\n");
        y++;
    }
}

void	ft_left(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->heigh && !x) {
		x = 0;
		while (x < game->width) {
			if (game->map2d[y][x] == 'P') {
				break;
			}
			x++;
		}
		if (x < game->width) {
			break;
		}
		y++;
	}

	if (x > 0 && game->map2d[y][x - 1] != '1' && game->map2d[y][x - 1] != 'E') {
		game->map2d[y][x] = '0';
		game->map2d[y][x - 1] = 'P';

		game->moves++;

		if (game->map2d[y][x - 1] == 'C') {
			game->coins--;
		}

		if (game->map2d[y][x - 1] == 'E' && game->coins == 0) {
			ft_error("You win!", 0);
		}
	}

	print_map(game);
}

void	ft_right(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->heigh && !x) {
		x = 0;
		while (x < game->width) {
			if (game->map2d[y][x] == 'P') {
				break;
			}
			x++;
		}
		if (x < game->width) {
			break;
		}
		y++;
	}

	if (x < game->width - 1 && game->map2d[y][x + 1] != '1' && game->map2d[y][x + 1] != 'E') {
		game->map2d[y][x] = '0';
		game->map2d[y][x + 1] = 'P';

		game->moves++;

		if (game->map2d[y][x + 1] == 'C') {
			game->coins--;
		}

		if (game->map2d[y][x + 1] == 'E' && game->coins == 0) {
			ft_error("You win!", 0);
		}
	}

	print_map(game);
}

void	ft_down(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->heigh && !x) {
		x = 0;
		while (x < game->width) {
			if (game->map2d[y][x] == 'P') {
				break;
			}
			x++;
		}
		if (x < game->width) {
			break;
		}
		y++;
	}

	if (y < game->heigh - 1 && game->map2d[y + 1][x] != '1' && game->map2d[y + 1][x] != 'E') {
		game->map2d[y][x] = '0';
		game->map2d[y + 1][x] = 'P';

		game->moves++;

		if (game->map2d[y + 1][x] == 'C') {
			game->coins--;
		}

		if (game->map2d[y + 1][x] == 'E' && game->coins == 0) {
			ft_error("You win!", 0);
		}
	}

	print_map(game);
}

void	ft_up(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->heigh && !x)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map2d[y][x] == 'P')
				break ;
			x++;
		}
		if (x < game->width)
			break ;
		y++;
	}
	if (y > 0 && game->map2d[y - 1][x] != '1'
		&& game->map2d[y - 1][x] != 'E')
	{
		game->map2d[y][x] = '0';
		game->map2d[y - 1][x] = 'P';
		game->moves++;
		if (game->map2d[y - 1][x] == 'C')
			game->coins--;
		if (game->map2d[y - 1][x] == 'E' && game->coins == 0)
			ft_error("You win!", 0);
	}

	print_map(game);
}



void	key_press(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_terminate(game->mlx);
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
