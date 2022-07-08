/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:49:00 by jmehlig           #+#    #+#             */
/*   Updated: 2022/05/04 12:38:59 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hex_to_deci(char *hex)
{
	int	y;
	int	deci;
	int	x;
	int	i;
	int	space;

	y = 0;
	deci = 0;
	space = 0;
	while (hex[space] != 'x')
		space++;
	i = ft_strlen(hex) - 1;
	while (i >= space + 1)
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			x = hex[i] - '0';
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			x = hex[i] - 'A' + 10;
		else
			x = hex[i] - 'a' + 10;
		deci = deci + x * pow(16, y);
		y++;
		i--;
	}
	return (deci);
}

int	get_newline_num(char *str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] != '\0')
			num++;
		i++;
	}
	num++;
	return (num);
}

int	get_colnum(char *str)
{
	int	num;
	int	i;

	num = 1;
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		if (str[i] == ' ' && str[i + 1] != '\n')
		{
			num++;
			while (str[i + 1] == ' ')
				i++;
		}
		i++;
	}
	return (num);
}

void	free_matrix(t_data *s)
{
	int	j;
	int	i;

	i = 0;
	printf("%i", 1);
	while ((s->matrix)[i])
	{
		j = 0;
		printf("%i ", i);
		printf("%i", j);
		while ((s->matrix)[i][j])
		{
			free((s->matrix)[i][j]);
			j++;
		}
		free((s->matrix)[i]);
		i++;
	}
	printf("\n");
	free(s->matrix);
}
