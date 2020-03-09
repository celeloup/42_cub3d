/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:58:29 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/02 14:17:48 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinfree(char *dest, char *src)
{
	void	*copy;
	int		dest_len;

	dest_len = ft_strlen(dest);
	if ((copy = (char*)malloc(sizeof(char) * (dest_len + 1))) == NULL)
		return (NULL);
	ft_strcpy(copy, dest);
	free(dest);
	dest = (char*)malloc(sizeof(char) * (dest_len + ft_strlen(src) + 1));
	if (dest == NULL)
		return (NULL);
	ft_strcpy(dest, copy);
	free(copy);
	ft_strcpy(dest + dest_len, src);
	return (dest);
}
