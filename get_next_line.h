/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:33:59 by abmasnao          #+#    #+#             */
/*   Updated: 2024/12/06 11:33:07 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*join(char *str, char *buf);
char	*cleanup(char **str, char **buf);
char	*inc_line(char *str);
char	*gnl(char **str);
char	*get_next_line(int fd);
char	*s_join(char **str, char *buf);

#endif