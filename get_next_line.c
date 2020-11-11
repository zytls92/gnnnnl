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

	if (!(*temp))// temp가 널이라는 것은 빈파일을 의미한다. 왜냐하면 처음 66번 쨰 줄에서 이 함수를 시작할 땐 temp가 존재할 때 돌아가니까 절대 이곳으로 들어올 수 없고 res = 0일 때 실행해야 이것을 만족 할 수 있다. 
	{
		*line = ft_strdup("\0");//널문자를 가진 문자열을 line에 넣고
		return (0);//0을 리턴한다.
	}
	len = ft_strlen(*temp);//temp가 가르키는 char *의 길이를 파악한다.
	if ((pos = ft_strchr(*temp, c)) != -1)//만약 temp가 가르키는 문자열에 c가 있다면 그 위치를 pos에 집어넣고
	{
		if (pos == 0)//pos가 0이면 첫번째가 개행이거나 널이라는 소리이므로
		{
			*line = ft_strdup("\0");//빈문자열 넣고
			if (len >= 1)// 빈문자열 들어왔을 떄 아래동작을 못하게  len이 1보다 크거나 같다는 조건을 달아놓음
				*temp = ft_substr(*temp, 1, len - 1, 1);
		}
		else//찾는 문자의 위치가 0번째가 아니라면
		{
			*line = ft_substr(*temp, 0, pos, 0);//위치 전까지 복사해서 line에 넣고 이때 temp를 free하면 안되니까 flag를 0으로주고
			*temp = ft_substr(*temp, pos + 1, len - pos, 1);//temp는 pos + 1 부터 len - pos개의 문자를 복사한다 이때 이전 temp는 free를 해줘야하므로 flag를 1로 놓음
		}
		return (1);
	}
	return (-1);
}

int		contcat_bt(char *buf, char **temp)
{
	if ((*temp) == NULL)//맨 처음 gnl 실행시 temp는 null일 것이므로 buf를 temp에다가 넣는다.
		*temp = ft_strdup(buf);
	else
		*temp = ft_strjoin(*temp, buf); //ft_strjoin을 하면서 temp += buf를 한다. 이때 이전 temp는 ft_strjoin에서 free한다. 1.이거 free 이런식으로 해도 되는건가요?
	return (ft_strchr(*temp, '\n'));//합치고나서 개행문자를 찾고 그 위치를 반환한다. 없다면 -1반환
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
	if (temp)// temp가 만약 비어 있지 않다면
		if (get_line(line, &temp, '\n') == 1)//혹시 그 안에 \n이 있는지 확인한다. 1이라는 것은 개행문자가 있다는 뜻이고 line에 집어넣고 라인에 넣었으니까 1을 반환.
			return (1);
	while ((res = read(fd, buf, BUFF_SIZE)) > 0)//read를 0보다 클때까지 반복한다. 그리고 read의 결과를 res에 집어넣는다.
		if ((pos = contcat_bt(buf, &temp)) != -1)// concat_bt를 통해서 buf와 temp를 합치고 합친 것을 temp에 집어넣는다. 그리고 넣어놓은 결과에 개행문자가 있다면 
			return (get_line(line, &temp, '\n'));//line에 집어넣는다.
	if (res == 0)//굳이 if문이 필요없을 수도,, read()의 결과가 0이면
	{
		get_line(line, &temp, '\0'); //널문자를 찾아서 그 전까지 집어넣고 마지막에 \0을 집어넣는다.
		free(temp);//temp는 필요 없으니까 free
		free(buf);//buf도 free
		buf = 0;
		temp = 0;
		return (0);
	}
	return (1);
}