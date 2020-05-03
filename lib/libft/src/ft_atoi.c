/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:30:59 by celeloup          #+#    #+#             */
/*   Updated: 2020/02/07 19:51:23 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nb)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	sign = '+';
	n = 0;
	while (nb[i] == ' ' || nb[i] == '\t' || nb[i] == '\n'
			|| nb[i] == '\v' || nb[i] == '\r' || nb[i] == '\f')
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		sign = nb[i];
		i++;
	}
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		n = n * 10;
		n = n + nb[i++] - 48;
		if (n < 0 && sign == '+')
			return (-1);
		if (n < 0 && sign == '-')
			return (0);
	}
	return ((sign == '+') ? n : -n);
}
