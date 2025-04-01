/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:57:44 by astefane          #+#    #+#             */
/*   Updated: 2025/04/01 22:06:11 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_exit(t_game *game, char c)
{
	if (c == 'E')
	{
		if (game->coins == 0)
		{
			ft_putstr("You win\n");
			mlx_terminate(game->mlx);
			exit(0);
		}
		else
			return (1);
	}
	return (0);
}

void print_map(t_game *game)
{
    int i = 0;

    while (game->big_line[i])
    {
        printf("%c", game->big_line[i]);
        if ((i + 1) % game->width == 0)
            printf("\n");

        i++;
    }
}

void	ft_left(t_game *game)
{
	int i;

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
	/* print_map(game); */
}

void	ft_right(t_game *game)
{
	int i;

	i = 0;
	while (game->big_line[i] != 'P')
		i++;
	if (game->big_line[i + 1] != '1'
		&& !check_exit(game, game->big_line[i + 1]))
	{
		if (game->big_line[i + 1] == 'C')
			game->coins--;
		if (game->big_line[i + 1] == 'E' && game->coins > 0)
			return;
		game->big_line[i] = '0';
		game->big_line[i + 1] = 'P';
		game->moves++;
		put_image(game, i);
		put_image(game, i + 1);
		ft_putstr("moves: ");
		ft_putnbr(game->moves);
		ft_putchar('\n');
	}
	/* print_map(game); */
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
		ft_putchar('\n');
		ft_putnbr(game->moves);
	}
	/* print_map(game); */
}

void	ft_up(t_game *game)
{
	int i;

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
	/* print_map(game); */
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
