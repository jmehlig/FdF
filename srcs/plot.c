/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:45:51 by jmehlig           #+#    #+#             */
/*   Updated: 2022/05/04 21:18:13 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *s, int color, t_points points)
{
	char		*dst;

	dst = s->addr + (points.y0 * s->line_l + points.x0 * (s->bpp / 8));
	*(unsigned int *)dst = color;
}

t_iso	to_isometric(int x, int y, t_data *s)
{
	t_iso	point;
	int		z;

	point.icolor = (s->matrix)[y][x][1];
	z = ((s->matrix)[y][x][0]) * s->zoom / 7 * s->z_shift;
	x = (x - s->col / 2) * s->zoom;
	y = (y - s->col / 2) * s->zoom;
	point.ix = (x - y) * cos(0.523599);
	point.iy = (-z) + (x + y) * cos(0.523599);
	point.ix += s->col / 2;
	point.iy += s->nl / 2;
	point.ix = point.ix * s->zoom;
	point.iy = point.iy * s->zoom;
	point.ix += s->x_shift;
	point.iy += s->y_shift;
	return (point);
}

int	line_color(t_iso old_p, t_iso new_p, int y)
{
	int	dy;
	int	between;
	int	new_color;

	dy = sqrt(pow(new_p.ix - old_p.ix, 2) + pow(new_p.iy - old_p.iy, 2));
	if (dy == 0)
		return (new_p.icolor);
	between = abs(new_p.icolor - old_p.icolor);
	if (between == 0)
		return (new_p.icolor);
	new_color = between / dy;
	return (new_p.icolor - (new_color * (y - new_p.iy)));
}

void	plot_line(t_iso old_p, t_iso new_p, t_data *s, t_bres b)
{
	t_points	points;

	points = s->points;
	while (1)
	{
		if (points.x0 < 1920 && points.x0 >= 0
			&& points.y0 < 1080 && points.y0 >= 0)
			my_mlx_pixel_put(s, line_color(old_p, new_p, points.y0), points);
		if (points.x0 == points.x1 && points.y0 == points.y1)
			break ;
		b.doub_err = 2 * b.err;
		if (b.doub_err >= b.dy)
		{
			b.err += b.dy;
			points.x0 += b.sx;
		}
		if (b.doub_err <= b.dx)
		{
			b.err += b.dx;
			points.y0 += b.sy;
		}
	}
}

void	bresenham(t_iso old_p, t_iso new_p, t_data *s)
{
	t_points	points;
	t_bres		b;

	points.x0 = old_p.ix;
	points.y0 = old_p.iy;
	points.x1 = new_p.ix;
	points.y1 = new_p.iy;
	b.dx = abs(points.x1 - points.x0);
	if (points.x0 < points.x1)
		b.sx = 1;
	else
		b.sx = -1;
	b.dy = -abs(points.y1 - points.y0);
	if (points.y0 < points.y1)
		b.sy = 1;
	else
		b.sy = -1;
	b.err = b.dx + b.dy;
	s->points = points;
	plot_line(old_p, new_p, s, b);
}
