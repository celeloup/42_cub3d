/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:32:55 by celeloup          #+#    #+#             */
/*   Updated: 2020/01/09 12:44:31 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t lendest;
	size_t lensrc;

	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	if (lendest < size)
	{
		ft_strncat(dest, src, size - lendest - 1);
		return (lensrc + lendest);
	}
	else
		return (lensrc + size);
}
