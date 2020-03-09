/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:35:08 by celeloup          #+#    #+#             */
/*   Updated: 2020/01/09 11:13:43 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nbdigit(int n)
{
	int		len;
	int		neg;

	neg = 0;
	len = 1;
	if (n < 0)
	{
		neg++;
		n = n * (-1);
	}
	while (n / 10 >= 1)
	{
		len++;
		n /= 10;
	}
	return (len + neg);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 0;
	len = nbdigit(n);
	str = (char*)malloc(len + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		neg++;
		str[0] = '-';
		n = n * (-1);
	}
	str[len] = '\0';
	len--;
	while (len >= neg)
	{
		str[len--] = n % 10 + 48;
		n = n / 10;
	}
	return (str);
}
