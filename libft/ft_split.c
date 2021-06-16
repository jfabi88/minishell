/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:25:59 by jfabi             #+#    #+#             */
/*   Updated: 2021/01/28 13:55:46 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lines(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

static void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != 0)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static int	new_lines(const char *s, char c, char **matrix)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != 0)
	{
		if (s[i] != c)
		{
			n = 0;
			while (s[i + n] != c && s[i + n] != 0)
				n++;
			matrix[j] = malloc(n + 1);
			if (matrix[j] == 0)
				return (-1);
			i += n;
			j++;
		}
		else
			i++;
	}
	matrix[j] = 0;
	return (j);
}

static void	cpy_mat(char const *s, char c, char **matrix)
{
	int	n;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != 0)
	{
		n = 0;
		while (s[i] == c)
			i++;
		while (s[i] != 0 && s[i] != c)
		{
			matrix[j][n] = s[i];
			n++;
			i++;
		}
		if (n != 0)
		{
			matrix[j][n] = 0;
			j++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	int		line;
	char	**matrix;

	if (s == 0)
		return (0);
	matrix = malloc((lines(s, c) + 1) * sizeof(char *));
	if (matrix == 0)
		return (0);
	line = new_lines(s, c, matrix);
	if (line == -1)
	{
		free_matrix(matrix);
		return (0);
	}
	cpy_mat(s, c, matrix);
	return (matrix);
}
