/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:44:49 by celeloup          #+#    #+#             */
/*   Updated: 2019/12/03 22:06:41 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list *new;

	if ((new = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (!content)
		new->content = NULL;
	else
	{
		if ((new->content = malloc(ft_strlen(content))) == NULL)
		{
			free(new);
			return (NULL);
		}
		ft_memcpy(new->content, content, ft_strlen(content) + 1);
	}
	new->next = NULL;
	return (new);
}
