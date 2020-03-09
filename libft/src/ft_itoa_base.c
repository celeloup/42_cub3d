/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:42:42 by celeloup          #+#    #+#             */
/*   Updated: 2020/02/11 10:57:21 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned long long value, char *base)
{
	int					count;
	unsigned long long	tmp;
	char				*res;
	unsigned long long	base_length;

	base_length = ft_strlen(base);
	count = (value < 0 && base_length == 10) ? 2 : 1;
	tmp = (value < 0 && base_length == 10) ? -value : value;
	while (tmp >= base_length && (tmp /= base_length))
		++count;
	tmp = (value < 0 && base_length == 10) ? -value : value;
	if (!(res = (char*)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	if (value < 0 && base_length == 10)
		res[0] = '-';
	res[count] = '\0';
	while (tmp >= base_length)
	{
		--count;
		res[count] = base[tmp % base_length];
		tmp /= base_length;
	}
	res[--count] = base[tmp % base_length];
	return (res);
}
