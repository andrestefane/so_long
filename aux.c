/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:17:55 by astefane          #+#    #+#             */
/*   Updated: 2025/04/08 14:23:15 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_game(t_game *game)
{
	if (game->big_line)
		free(game->big_line);
	free(game);
}

int	check_exit(t_game *game, char c)
{
	if (c == 'E')
	{
		if (game->coins == 0)
		{
			game->moves++;
			ft_putstr("moves: ");
			ft_putnbr(game->moves);
			ft_putchar('\n');
			ft_putstr("\033[1;32mYou win\n\033[0m");
			destroy_imagen(game);
			mlx_terminate(game->mlx);
			exit(0);
		}
		else
			return (1);
	}
	return (0);
}

void	parsing(t_game *game, char *map)
{
	check_img(game);
	check_map_name(game, map);
	reading_map(game, map);
	check_len(game);
	check_map(game);
	game->mlx = mlx_init(game->width * 64, game->heigh * 64, "so_long", false);
	if (!game->mlx)
	{
		ft_putstr(" Error\n Failed to initialize mlx\n");
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

void	check_map_name(t_game *game, char *map)
{
	int		fd;
	char	buffer[2];
	int		bytes_read;

	if (ft_strlen(map) <= 4
		|| ft_strncmp(map + ft_strlen(map) - 4, ".ber", 4) != 0)
		ft_error_and_free(game, " Error\n .ber not found\n", 1);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_error_and_free(game, " Error\n Can't open map\n", 1);
	bytes_read = read(fd, buffer, 1);
	if (bytes_read <= 0)
	{
		close(fd);
		ft_error_and_free(game, " Error\n Map is empty\n", 1);
	}
	close(fd);
}

void	check_len(t_game *game)
{
	game->size_heigh = 3840;
	game->size_width = 2160;
	if (game->heigh * 64 > game->size_width
		|| game->width * 64 > game->size_heigh)
		ft_error_and_free(game, " Error\n Map too Big\n", 1);
}
