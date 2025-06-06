/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:52:33 by astefane          #+#    #+#             */
/*   Updated: 2025/04/07 19:26:34 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_left(t_game *game)
{
	int	i;

	i = 0;
	while (game->big_line[i] != 'P')
		i++;
	if (game->big_line[i - 1] != '1'
		&& !check_exit(game, game->big_line[i - 1]))
	{
		if (game->big_line[i - 1] == 'C')
			game->coins--;
		game->big_line[i] = '0';
		game->big_line[i - 1] = 'P';
		if (game->big_line[i - game->width] == 'E')
			game->exit = 1;
		game->moves++;
		put_image(game, i);
		put_image(game, i - 1);
		ft_putstr("moves: ");
		ft_putnbr(game->moves);
		ft_putchar('\n');
	}
}

void	ft_right(t_game *game)
{
	int	i;

	i = 0;
	while (game->big_line[i] != 'P')
		i++;
	if (game->big_line[i + 1] != '1'
		&& !check_exit(game, game->big_line[i + 1]))
	{
		if (game->big_line[i + 1] == 'C')
			game->coins--;
		if (game->big_line[i + 1] == 'E' && game->coins > 0)
			return ;
		game->big_line[i] = '0';
		game->big_line[i + 1] = 'P';
		game->moves++;
		put_image(game, i);
		put_image(game, i + 1);
		ft_putstr("moves: ");
		ft_putnbr(game->moves);
		ft_putchar('\n');
	}
}

void	ft_down(t_game *game)
{
	int	i;

	i = 0;
	while (game->big_line[i] != 'P')
		i++;
	if (game->big_line[i + game->width] != '1'
		&& !check_exit(game, game->big_line[i + game->width]))
	{
		if (game->big_line[i + game->width] == 'C')
			game->coins--;
		game->big_line[i] = '0';
		game->big_line[i + game->width] = 'P';
		if (game->big_line[i - game->width] == 'E')
			game->exit = 1;
		game->moves++;
		put_image(game, i);
		put_image(game, i + game->width);
		ft_putstr("moves: ");
		ft_putnbr(game->moves);
		ft_putchar('\n');
	}
}

void	ft_up(t_game *game)
{
	int	i;

	i = 0;
	while (game->big_line[i] != 'P')
		i++;
	if (game->big_line[i - game->width] != '1'
		&& !check_exit(game, game->big_line[i - game->width]))
	{
		if (game->big_line[i - game->width] == 'C')
			game->coins--;
		game->big_line[i] = '0';
		game->big_line[i - game->width] = 'P';
		game->moves++;
		put_image(game, i);
		put_image(game, i - game->width);
		ft_putstr("moves: ");
		ft_putnbr(game->moves);
		ft_putchar('\n');
	}
}

void	destroy_imagen(t_game *game)
{
	mlx_delete_image(game->mlx, game->img_background);
	mlx_delete_image(game->mlx, game->img_coin);
	mlx_delete_image(game->mlx, game->img_wall);
	mlx_delete_image(game->mlx, game->img_exit);
	mlx_delete_image(game->mlx, game->img_player);
	mlx_close_window(game->mlx);
}
