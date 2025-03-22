/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:02:39 by astefane          #+#    #+#             */
/*   Updated: 2025/03/22 18:46:20 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "./minilib/mlx_int.h"
# include "./minilib/mlx.h"

typedef struct game
{
	void	*mlx;
	void	*window;
	void	*start;
	int		coins;
	int		moves;
	int		errors;
	int		wall;
	int		*x;
	int		*y;

}	t_game;


#endif