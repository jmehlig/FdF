/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:09:35 by jmehlig           #+#    #+#             */
/*   Updated: 2022/05/04 18:11:20 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*to_str(int fd)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	str = ft_calloc(1, 1);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		tmp2 = str;
		str = ft_strjoin(str, tmp);
		free(tmp2);
		ft_free(tmp);
	}
	return (str);
}

void	ft_point_colors(t_data *s, char **columns, int i, int j)
{
	s->matrix[i][j] = (int *)ft_calloc(2, sizeof(int));
	if (!s->matrix[i][j])
		exit(1);
	(s->matrix)[i][j][0] = ft_atoi(columns[j]);
	if (ft_strchr(columns[j], 'x'))
		(s->matrix)[i][j][1] = hex_to_deci(columns[j]);
	else
		(s->matrix)[i][j][1] = hex_to_deci("xffffff");
}

void	ft_make_points(t_data *s, char *str)
{
	char	**lines;
	char	**columns;
	int		i;
	int		j;

	i = 0;
	lines = ft_split(str, '\n');
	while (lines[i])
	{
		columns = ft_split(lines[i], ' ');
		(s->matrix)[i] = (int **)ft_calloc(s->col * 2, sizeof(int *));
		if (!(s->matrix)[i])
			exit(1);
		j = 0;
		while (columns[j])
		{
			ft_point_colors(s, columns, i, j);
			j++;
		}
		i++;
		ft_splitdel(&columns);
	}
	ft_splitdel(&lines);
}

void	error(char *str)
{
	int	columns;

	if (str[0] == 0)
		exit(0);
	columns = get_colnum(str);
	if (columns == 1)
		exit(1);
	while (*str != '\n')
		str++;
	str++;
	while (*str)
	{
		if (get_colnum(str) != columns)
			exit (1);
		while (*str != '\n' && *str)
			str++;
		str++;
	}
}

void	get_data(int fd, t_data *s)
{
	char	*str;

	str = to_str(fd);
	error(str);
	s->nl = get_newline_num(str);
	s->col = get_colnum(str);
	s->matrix = (int ***)ft_calloc(s->nl * s->col, sizeof(int **));
	if (!s->matrix)
		exit(1);
	ft_make_points(s, str);
	free(str);
}
