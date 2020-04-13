/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:41:32 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/10 13:14:13 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

int		clean_return(char **ptr, char **ptr2, int ret)
{
	if (ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (ptr2 != NULL)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	return (ret);
}

int		find_nl(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

int		read_line(int fd, char **line, char *buff)
{
	int		ret;
	int		nl_char;
	char	*tmp;

	if ((tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (clean_return(line, NULL, -1));
	while ((ret = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[ret] = '\0';
		if ((nl_char = find_nl(tmp)) != -1)
		{
			ft_strcpy(buff, tmp + nl_char + 1);
			tmp[nl_char] = '\0';
			if ((*line = ft_strjoinfree(*line, tmp)) == NULL)
				return (clean_return(&tmp, NULL, -1));
			return (clean_return(&tmp, NULL, 1));
		}
		if ((*line = ft_strjoinfree(*line, tmp)) == NULL)
			return (clean_return(&tmp, NULL, -1));
	}
	if (ret == -1)
		return (clean_return(&tmp, line, -1));
	if (*line[0] != '\0')
		return (clean_return(&tmp, NULL, 1));
	return (clean_return(&tmp, line, ret));
}

int		get_next_line(int fd, char **line)
{
	int			nl_char;
	static char	buff[_SC_OPEN_MAX][BUFFER_SIZE + 1] = {{0}};

	if (fd < 0 || fd > _SC_OPEN_MAX || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if ((*line = ft_strdup("")) == NULL)
		return (-1);
	if (buff[fd][0] == '\0')
		return (read_line(fd, line, buff[fd]));
	if ((nl_char = find_nl(buff[fd])) != -1)
	{
		free(*line);
		if ((*line = (char *)malloc(sizeof(char) * (nl_char + 1))) == NULL)
			return (-1);
		ft_strncpy(*line, buff[fd], nl_char + 1);
		(*line)[nl_char] = '\0';
		ft_strcpy(buff[fd], buff[fd] + nl_char + 1);
		return (1);
	}
	free(*line);
	if (!(*line = (char*)malloc(sizeof(char) * (ft_strlen(buff[fd]) + 1))))
		return (-1);
	ft_strcpy(*line, buff[fd]);
	buff[fd][0] = '\0';
	return (read_line(fd, line, buff[fd]));
}
