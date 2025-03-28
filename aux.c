/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:17:55 by astefane          #+#    #+#             */
/*   Updated: 2025/03/28 08:47:41 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_dup_big_line(char **dup_big_line)
{
	char	**ptr;

	ptr = dup_big_line;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(dup_big_line);
}

void	parsing(t_game *game, char *map)
{
	check_map_name(map);
	reading_map(game, map);
	check_dup_map(game);
	game->mlx = mlx_init(game->width * 64, game->heigh * 64, "so_long", false);
	load_img(game);
	place(game);
	mlx_key_hook(game->mlx, &key_press, game);
	mlx_loop(game->mlx);

}
