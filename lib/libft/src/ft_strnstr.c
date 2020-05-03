/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:29:02 by celeloup          #+#    #+#             */
/*   Updated: 2019/12/02 16:29:22 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub_str, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (sub_str[0] == '\0')
		return ((char *)&str[0]);
	while (str[i] && i < n)
	{
		if (str[i] == sub_str[j])
		{
			j = 0;
			while (str[i + j] == sub_str[j] && i + j < n)
			{
				j++;
				if (sub_str[j] == '\0')
					return ((char *)&str[i]);
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
