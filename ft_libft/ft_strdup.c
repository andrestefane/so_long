/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:49:35 by astefane          #+#    #+#             */
/*   Updated: 2025/04/07 19:18:53 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s1);
	if (!*s1)
		return (NULL);
	dup = (char *)malloc(len + 1);
	if (dup != NULL)
	{
		ft_strlcpy(dup, s1, len + 1);
	}
	return (dup);
}
