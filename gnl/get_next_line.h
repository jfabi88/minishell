/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:44:58 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/16 15:42:12 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

# define BUFFER_SIZE 10

char	*copia(char *s1, const char *s2);
int		ft_strlenn(const char *s);
int		ft_get_next_line(int fd, char **line);

#endif
