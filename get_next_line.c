/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:32:27 by abmasnao          #+#    #+#             */
/*   Updated: 2024/12/06 17:25:53 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*inc_line(char *str)
{
	char	*line;
	int		index;

	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	if (str[index] == '\n')
		line = malloc(index + 2);
	else
		line = malloc(index + 1);
	if (!line)
		return (NULL);
	index = 0;
	while (str[index] && str[index] != '\n')
	{
		line[index] = str[index];
		index++;
	}
	if (str[index] == '\n')
		line[index++] = '\n';
	line[index] = '\0';
	return (line);
}

char	*gnl(char **str)
{
	int		index;
	int		count;
	char	*new_line;

	if (!*str || !**str)
		return (NULL);
	index = 0;
	while ((*str)[index] && (*str)[index] != '\n')
		index++;
	new_line = malloc(ft_strlen(*str) - index + 1);
	if (!new_line)
		return (NULL);
	count = 0;
	if ((*str)[index] == '\n')
		index++;
	while ((*str)[index])
		new_line[count++] = (*str)[index++];
	new_line[count] = '\0';
	free(*str);
	*str = NULL;
	if (*new_line == '\0')
		return (free(new_line), new_line = NULL, new_line);
	return (new_line);
}

int	check_nl(char *buf)
{
	int	i;

	i = 0;
	if (!buf || !*buf)
		return (0);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf;
	ssize_t		count;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	count = 1;
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (count > 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 0)
			return (cleanup(&str, &buf));
		buf[count] = '\0';
		str = s_join(&str, buf);
		if (check_nl(buf) == 1)
			break ;
	}
	free(buf);
	buf = NULL;
	if (count == 0 && (!str || !*str))
		return (cleanup(&str, &buf));
	return (buf = inc_line(str), str = gnl(&str), buf);
}
