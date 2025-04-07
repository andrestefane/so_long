/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:13:52 by astefane          #+#    #+#             */
/*   Updated: 2025/04/07 19:42:05 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_map(t_game *game)
{
	char	*dup_big_line;
	int		start_pos;

	game->copy_coins = game->coins;
	dup_big_line = ft_strdup(game->big_line);
	if (!dup_big_line)
		ft_error_and_free(game, "Error\nmemory allocation\n", 0);
	start_pos = ft_find_player(dup_big_line);
	if (start_pos == -1)
	{
		free(dup_big_line);
		ft_error_and_free(game, "Error\nno player found\n", 0);
	}
	ft_flood_flip(game, start_pos, dup_big_line);
	if (game->copy_coins != 0)
	{
		free(dup_big_line);
		ft_error_and_free(game, "Error\nno path to all coins\n", 0);
	}
	if (!is_exit_reachable(game, dup_big_line))
	{
		free(dup_big_line);
		ft_error_and_free(game, "Error\nno path to exit\n", 0);
	}
	free(dup_big_line);
}

void	ft_flood_flip(t_game *game, int x, char *map)
{
	if (x < 0 || x >= game->width * game->heigh)
		return ;
	if (map[x] == '1' || map[x] == 'F' || map[x] == 'E')
		return ;
	if (map[x] == 'C')
		game->copy_coins--;
	map[x] = 'F';
	ft_flood_flip(game, x + 1, map);
	ft_flood_flip(game, x - 1, map);
	ft_flood_flip(game, x + game->width, map);
	ft_flood_flip(game, x - game->width, map);
}

int	is_exit_reachable(t_game *game, char *map)
{
	int	i;
	int	right;
	int	left;
	int	down;
	int	up;

	i = 0;
	while (map[i])
	{
		if (map[i] == 'E')
		{
			right = i + 1;
			left = i - 1;
			down = i + game->width;
			up = i - game->width;
			if ((right < game->width * game->heigh && map[right] == 'F')
				|| (left >= 0 && map[left] == 'F')
				|| (down < game->width * game->heigh && map[down] == 'F')
				|| (up >= 0 && map[up] == 'F'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_find_player(char *big_line)
{
	int	i;

	i = 0;
	while (big_line[i])
	{
		if (big_line[i] == 'P')
			return (i);
		i++;
	}
	return (-1);
}
