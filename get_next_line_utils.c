/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcho <mcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:19:23 by mcho              #+#    #+#             */
/*   Updated: 2020/11/11 15:01:50 by mcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int		ft_strchr(char *s, char c)
{
	int		idx;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == c)
			return (idx);
		idx++;
	}
	if (c == '\0')
		return (idx);
	return (-1);
}

char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (*(s + len) != '\0')
		len++;
	if ((res = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	i = 0;
	if ((res = malloc(sizeof(char) *
					(ft_strlen((char *)s1) + ft_strlen((char *)s2)) + 1))
							== NULL)
		return (NULL);
	while (i < ft_strlen((char *)s1) + ft_strlen((char *)s2))
	{
		if (i < ft_strlen((char *)s1))
			res[i] = s1[i];
		else
			res[i] = s2[i - ft_strlen((char *)s1)];
		i++;
	}
	free((char *)s1);
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, int len, int flag)
{
	char		*res;
	int			i;

	if (!s)
		return (ft_strdup(""));
	if ((int)start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	if ((res = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	if (flag == 1)
		free((char *)s);
	return (res);
}
