/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:12:19 by jmehlig           #+#    #+#             */
/*   Updated: 2022/05/04 21:16:18 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	create_new_map(t_data s)
{
	if (s.mlx != NULL)
		mlx_destroy_window(s.mlx, s.win);
	if (s.img != NULL)
		mlx_destroy_image(s.mlx, s.img);
	s.win = mlx_new_window(s.mlx, 1920, 1080, "FdF");
	s.img = mlx_new_image(s.mlx, 1920, 1080);
	s.addr = mlx_get_data_addr(s.img, &(s.bpp), &(s.line_l), &(s.end));
	my_mlx_matrix_put(&s);
	mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
	mlx_hook(s.win, 2, 1L << 0, ft_exit, &s);
	mlx_hook(s.win, 17, 1L << 17, ex, &s);
	mlx_key_hook(s.win, keys, &s);
	mlx_loop(s.mlx);
}

int	keycode_check(int keycode)
{
	if (keycode == 69 || keycode == 78 || keycode == 125 || keycode == 126
		|| keycode == 0 || keycode == 2 || keycode == 13 || keycode == 1)
		return (1);
	return (0);
}

int	keys(int keycode, t_data	*s_in)
{
	t_data	s;

	s = *s_in;
	printf("%d\n", keycode);
	if (keycode == 69)
		s.zoom++;
	if (keycode == 78 && s.zoom > 1)
		s.zoom--;
	if (keycode == 125)
		s.z_shift++;
	if (keycode == 126)
		s.z_shift--;
	if (keycode == 0)
		s.x_shift -= 10;
	if (keycode == 2)
		s.x_shift += 10;
	if (keycode == 1)
		s.y_shift += 10;
	if (keycode == 13)
		s.y_shift -= 10;
	if (keycode_check(keycode))
		create_new_map(s);
	return (0);
}
