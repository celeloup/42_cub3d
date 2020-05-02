/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:07:43 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/02 17:26:09 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		split_len_tab(char const *s, char c)
{
	int len;
	int i;

	len = 0;
	i = 0;
	if (s[0] != c && s[0] != '\0')
		len++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			len++;
		i++;
	}
	return (len);
}

static void		fill_tab(char **tab, char const *s, char c)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i + len] && s[i + len] != c)
				len++;
			tab[j] = (char*)malloc(sizeof(char) * len + 1);
			len = 0;
			while (s[i] && s[i] != c)
				tab[j][len++] = s[i++];
			tab[j++][len] = '\0';
		}
		else
			i++;
	}
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	int		len;

	if (!s)
		return (NULL);
	len = split_len_tab(s, c);
	tab = (char **)malloc(sizeof(char*) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len] = NULL;
	fill_tab(tab, s, c);
	return (tab);
}
