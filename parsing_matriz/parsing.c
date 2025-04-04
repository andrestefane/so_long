/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:13:52 by astefane          #+#    #+#             */
/*   Updated: 2025/04/02 18:43:53 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_map(t_game *game)
{
	char	*dup_big_line;
	int		start_pos;

	game->copy_coins = game->coins;
	dup_big_line = NULL;
	dup_big_line = ft_strdup(game->big_line);
	start_pos = ft_find_player(dup_big_line);
	ft_flood_flip(game, start_pos, dup_big_line);
	if (game->copy_coins != 0 || game->exit != 0)
	{
		free(dup_big_line);
		ft_error("Error no path\n", 0);
	}
	if (!check_end(game) || !check_player(game))

	{
		free(dup_big_line);
		ft_error("Error no path\n", 0);
	}
	free(dup_big_line);
}

void	ft_flood_flip(t_game *game, int x, char *map)
{
	if (x < 0 || x >= game->width * game->heigh)
		return ;
	if (map[x] == '1' || map[x] == 'F')
		return ;
	if (map[x] == 'C')
		game->copy_coins--;
	if (map[x] == 'E')
		game->exit--;
	map[x] = 'F';
	ft_flood_flip(game, x + 1, map);
	ft_flood_flip(game, x - 1, map);
	ft_flood_flip(game, x + game->width, map);
	ft_flood_flip(game, x - game->width, map);

}

int	check_dup_line(char *dup_big_line)
{
	int	i;
	int	path;

	i = 0;
	path = 0;
	while (dup_big_line[i])
	{
		if (dup_big_line[i] == 'F')
			path = 1;
		i++;
	}
	printf("Esto es dup_line %s\n", dup_big_line);
	if (path == 0)
		ft_error("Error no path\n", 0);
	return (path);
}

int	check_player(t_game *game)
{
	int	i;
	int	path;

	i = 0;
	path = 0;
	while (game->big_line[i])
	{
		if (game->big_line[i] == 'P')
		{
			if (game->big_line[i + 1] == '0' || game->big_line[i - 1] == '0'
				|| game->big_line[i + game->width] == '0'
				|| game->big_line[i - game->width] == '0')
				path = 1;
			if (game->big_line[i + 1] == 'C' || game->big_line[i - 1] == 'C'
				|| game->big_line[i + game->width] == 'C'
				|| game->big_line[i - game->width] == 'C')
				path = 1;
		}
		i++;
	}
		if (path == 0)
			ft_error("Error no path\n", 0);
	return (path);
}

int	check_end(t_game *game)
{
	int	i;
	int	path;

	i = 0;
	path = 0;
	while (game->big_line[i])
	{
		if (game->big_line[i] == 'E')
		{
			if (game->big_line[i + 1] == '0' || game->big_line[i - 1] == '0'
				|| game->big_line[i + game->width] == '0'
				|| game->big_line[i - game->width] == '0')
				path = 1;
			if (game->big_line[i + 1] == 'C' || game->big_line[i - 1] == 'C'
				|| game->big_line[i + game->width] == 'C'
				|| game->big_line[i - game->width] == 'C')
				path = 1;
		}
		i++;
	}
		if (path == 0)
			ft_error("Error no path\n", 0);
	return (path);
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
int	check_exit_reachable(char *map)
{
	int i = 0;
	while (map[i])
	{
		if (map[i] == 'E')
			return (0);
		i++;
	}
	return (1);
}