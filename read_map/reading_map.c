/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:23:22 by astefane          #+#    #+#             */
/*   Updated: 2025/04/08 15:49:06 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_check_side(t_game *game)
{
	int	i;

	i = game->width - 1;
	while (i < ft_strlen(game->big_line))
	{
		if (game->big_line[i] != '1')
			ft_error_and_free(game, " Error\n right side\n", 0);
		i += game->width;
	}
	i = 0;
	while (i < ft_strlen(game->big_line))
	{
		if (game->big_line[i] != '1')
			ft_error_and_free(game, " Error\n left side\n", 0);
		i += game->width;
	}
}

void	ft_check_top_bot(t_game *game)
{
	int		i;
	int		last;

	i = 0;
	last = ft_strlen(game->big_line) - game->width;
	while (i != game->width)
	{
		if (game->big_line[i] == '1' || game->big_line[i] == '\n')
			i++;
		else
			ft_error_and_free(game, " Error\ntop\n", 0);
	}
	while (last != ft_strlen(game->big_line))
	{
		if (game->big_line[last] == '1' || game->big_line[last] == '\n')
			last++;
		else
			ft_error_and_free(game, " Error\nbottom\n", 0);
	}
	ft_check_side(game);
}

void	ft_check_obligatory(t_game *game)
{
	int	i;

	i = 0;
	while (game->big_line[i])
	{
		if (game->big_line[i] != 'C' && game->big_line[i] != 'E'
			&& game->big_line[i] != '1' && game->big_line[i] != '0'
			&& game->big_line[i] != 'P' && game->big_line[i] != '\n')
			ft_error_and_free(game, " Error\nWrong characters\n", 0);
		if (game->big_line[i] == 'C')
			game->coins++;
		if (game->big_line[i] == 'E')
			game->exit++;
		if (game->big_line[i] == '1')
			game->wall++;
		if (game->big_line[i] == '0')
			game->background++;
		if (game->big_line[i] == 'P')
			game->player++;
		i++;
	}
	if (game->coins < 1 || game->exit != 1
		|| game->wall < 1 || game->player != 1)
		ft_error_and_free(game, " Error\nWrong characters\n", 0);
}

void	reading_map(t_game *game, char *map)
{
	int		fd;
	char	*temp_big_line;

	temp_big_line = ft_strdup("");
	if (!temp_big_line)
		ft_error_and_free(game, " Error\nMemory allocation failed\n", 1);
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		free(temp_big_line);
		ft_error_and_free(game, " Error\nCan't open map\n", 1);
	}
	process_map_lines(game, fd, &temp_big_line);
	if (!temp_big_line)
	{
		close(fd);
		ft_error_and_free(game, " Error\nMap is empty\n", 1);
	}
	game->big_line = ft_strdup(temp_big_line);
	free(temp_big_line);
	close(fd);
	ft_check_top_bot(game);
	ft_check_obligatory(game);
}

void	process_map_lines(t_game *game, int fd, char **temp_big_line)
{
	char	*line;
	int		line_len;

	while (1)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		game->heigh++;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		line_len = ft_strlen(line);
		if (game->width == 0)
			game->width = line_len;
		else if (line_len != game->width)
		{
			free(line);
			free(*temp_big_line);
			get_next_line(fd, 1);
			ft_error_and_free(game, " Error\nMap is not rectangular\n", 1);
		}
		*temp_big_line = ft_strjoin(*temp_big_line, line);
		free(line);
	}
	get_next_line(fd, 1);
}
