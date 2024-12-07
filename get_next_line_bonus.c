/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:28:36 by abmasnao          #+#    #+#             */
/*   Updated: 2024/12/06 16:51:12 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*str[OPEN_MAX];
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
			return (cleanup(&str[fd], &buf));
		buf[count] = '\0';
		str[fd] = s_join(&str[fd], buf);
		if (check_nl(buf) == 1)
			break ;
	}
	free(buf);
	buf = NULL;
	if (count == 0 && (!str[fd] || !*str[fd]))
		return (cleanup(&str[fd], &buf));
	return (buf = inc_line(str[fd]), str[fd] = gnl(&str[fd]), buf);
}
