/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:13:52 by astefane          #+#    #+#             */
/*   Updated: 2025/04/01 20:09:14 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_dup_map(t_game *game)
{
	int		i;
	char	**dup_big_line;

	i = 0;
	dup_big_line = (char **)malloc(sizeof(char *) * (game->heigh + 1));
	if (!dup_big_line)
		ft_error("Error in dup_map\n", 1);
	while (i < game->heigh)
	{
		dup_big_line[i] = ft_strndup(game->big_line + i * game->width,
				game->width);
		if (!dup_big_line[i])
		{
			while (--i >= 0)
				free(dup_big_line[i]);
			free(dup_big_line);
			return ;
		}
		i++;
	}
	dup_big_line[i] = NULL;
	allocate_map2d(game, dup_big_line);
}

void	allocate_map2d(t_game *game, char **dup_big_line)
{
	game->map2d = (char **)malloc(sizeof(char *) * game->heigh);
	if (!game->map2d)
		ft_error("Error allocating 2D map\n", 1);
	copy_to_map2d(game, dup_big_line);
	free_dup_big_line(dup_big_line);
	ft_flood_flip(game, 0, 0, game->map2d);
	print_map(game);
	if (!check_matriz(game))
	{
		free_dup_big_line(game->map2d);
		free(game);
		ft_error("Error no path\n", 0);
	}
}

void	ft_flood_flip(t_game *game, int y, int x, char **map)
{
	if (x < 0 || y < 0 || x >= game->width
		|| y >= game->heigh
		|| map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'E')
		return ;
	map[y][x] = 'X';
	ft_flood_flip(game, y + 1, x, map);
	ft_flood_flip(game, y - 1, x, map);
	ft_flood_flip(game, y, x + 1, map);
	ft_flood_flip(game, y, x - 1, map);
}

int	check_matriz(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->heigh)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map2d[y][x] == 'E')
			{
				if ((y > 0 && game->map2d[y - 1][x] == '0')
					|| (y < game->heigh - 1 && game->map2d[y + 1][x] == '0')
					|| (x > 0 && game->map2d[y][x - 1] == '0')
					|| (x < game->width - 1 && game->map2d[y][x + 1] == '0'))
					return (1);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (0);
}


void	copy_to_map2d(t_game *game, char **dup_big_line)
{
	int		i;
	char	**ptr;
	char	**line_ptr;

	ptr = game->map2d;
	line_ptr = dup_big_line;
	i = 0;
	while (i < game->heigh)
	{
		*ptr = ft_strdup(*line_ptr);
		if (!*ptr)
		{
			while (--ptr >= game->map2d)
				free(*ptr);
			free(game->map2d);
			return ;
		}
		ptr++;
		line_ptr++;
		i++;
	}
}