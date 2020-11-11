/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcho <mcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:18:47 by mcho              #+#    #+#             */
/*   Updated: 2020/11/11 15:31:52 by mcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFF_SIZE 2
#include "get_next_line.h"
#include <stdio.h>

int		get_line(char **line, char **temp, char c)
{
	int		pos;
	int		len;

	if (!(*temp))
	{
		*line = ft_strdup("\0");
		return (0);
	}
	len = ft_strlen(*temp);
	if ((pos = ft_strchr(*temp, c)) != -1)
	{
		if (pos == 0)
		{
			*line = ft_strdup("\0");
			if (len > 1)
				*temp = ft_substr(*temp, 1, len - 1, 1);
		}
		else
		{
			*line = ft_substr(*temp, 0, pos, 0);
			*temp = ft_substr(*temp, pos + 1, len - pos, 1);
		}
		return (1);
	}
	return (-1);
}

int		contcat_bt(char *buf, char **temp)
{
	if ((*temp) == NULL)
		*temp = ft_strdup(buf);
	else
		*temp = ft_strjoin(*temp, buf);
	return (ft_strchr(*temp, '\n'));
}

int		get_next_line(int fd, char **line)
{
	static	char	*temp;
	char			*buf;
	int				pos;
	int				res;

	if ((fd < 0) || (line == NULL) || (BUFF_SIZE < 0))
		return (-1);
	if ((buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
		return (-1);
	if (temp)
		if (get_line(line, &temp, '\n') == 1)
			return (1);
	while ((res = read(fd, buf, BUFF_SIZE)) > 0)
		if ((pos = contcat_bt(buf, &temp)) != -1)
			return (get_line(line, &temp, '\n'));
	if (res == 0)
	{
		get_line(line, &temp, '\0');
		free(temp);
		free(buf);
		buf = 0;
		temp = 0;
		return (0);
	}
	return (1);
}