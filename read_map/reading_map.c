/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:23:22 by astefane          #+#    #+#             */
/*   Updated: 2025/04/02 19:09:27 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_map_name(t_game *game, char *map)
{
	int		fd;
	char	buffer[2];
	int		bytes_read;

	if (ft_strlen(map) <= 4 || ft_strncmp(map + ft_strlen(map) - 4, ".ber", 4) != 0)
		ft_error_and_free(game, "Error .ber not found\n", 1);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_error_and_free(game, "Error Can't open map\n", 1);
	bytes_read = read(fd, buffer, 1);
	if (bytes_read <= 0)
	{
		close(fd);
		ft_error_and_free(game, "Error Map is empty\n", 1);
	}
	close(fd);
}

void	ft_check_side(t_game *game)
{
	int	i;

	i = game->width - 1;
	while (i < ft_strlen(game->big_line))
	{
		if (game->big_line[i] != '1')
			ft_error_and_free(game, "Error right side\n", 0);
		i += game->width;
	}
	i = 0;
	while (i < ft_strlen(game->big_line))
	{
		if (game->big_line[i] != '1')
			ft_error_and_free(game, "Error left side\n", 0);
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
			ft_error_and_free(game, "Error in top\n", 0);
	}
	while (last != ft_strlen(game->big_line))
	{
		if (game->big_line[last] == '1' || game->big_line[last] == '\n')
			last++;
		else
			ft_error_and_free(game, "Error in bottom\n", 0);
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
			ft_error_and_free(game, "Error Wrong characters\n", 0);
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
		ft_error_and_free(game, "Error Wrong characters or map configuration\n", 0);
}


void	Check_map_limits(char *line, t_game *game)
{
	if (line[ft_strlen(line) - 1] == '\n')
		game->count_line = 0;
	else
		game->count_line = 1;
}

void	reading_map(t_game *game, char *map)
{
	int 	fd;
	char	*line;
	char	*temp_big_line;

	temp_big_line = ft_strdup("");
	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_error_and_free(game, "Error Can't open map\n", 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->heigh++;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		game->width = ft_strlen(line);
		temp_big_line = ft_strjoin(temp_big_line, line);
		free(line);
	}
	game->big_line = ft_strdup(temp_big_line);
	free(temp_big_line);
	close(fd);
	ft_check_top_bot(game);
	ft_check_obligatory(game);
}
