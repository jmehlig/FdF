/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:13:14 by jmehlig           #+#    #+#             */
/*   Updated: 2022/05/04 12:49:04 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_matrix_put(t_data *s)
{
	int		x;
	int		y;
	t_iso	new_p;
	t_iso	old_p;

	y = 0;
	while ((s->matrix)[y])
	{
		x = 0;
		while ((s->matrix)[y][x])
		{
			new_p = to_isometric(x, y, s);
			if (x > 0)
				bresenham(old_p, new_p, s);
			if (y > 0)
				bresenham(to_isometric(x, y - 1, s), new_p, s);
			old_p = new_p;
			x++;
		}
		y++;
	}
}

void	ft_init(t_data *s)
{
	s->zoom = 30 - s->col / 2;
	if (s->zoom <= 0)
		s->zoom = 1;
	s->x_shift = 960 - (s->col / 4);
	s->y_shift = 540 - (s->nl / 4);
}

int	ft_keycodes(int keycode, t_data *s)
{
	if (keycode == 53)
		exit(0);
	mlx_destroy_image(s->mlx, s->img);
	s->img = mlx_new_image(s->mlx, 1920, 1080);
	s->addr = mlx_get_data_addr(s->img, &(s->bpp), &(s->line_l), &(s->end));
	my_mlx_matrix_put(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	return (0);
}

int	ex(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_data	s;
	char	*src;

	if (argc != 2)
		return (0);
	src = ft_strjoin("./test_maps/", argv[1]);
	fd = open(src, O_RDONLY);
	if (fd < 0)
		return (0);
	get_data(fd, &s);
	ft_init(&s);
	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, 1920, 1080, "FdF");
	s.img = mlx_new_image(s.mlx, 1920, 1080);
	s.addr = mlx_get_data_addr(s.img, &(s.bpp), &(s.line_l), &(s.end));
	my_mlx_matrix_put(&s);
	mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
	mlx_hook(s.win, 2, 1L << 0, ft_keycodes, &s);
	mlx_hook(s.win, 17, 1L << 17, ex, &s);
	mlx_loop(s.mlx);
	free(src);
	free_matrix(&s);
	// system("leaks fdf");
	// while (1);
	return (0);
}
