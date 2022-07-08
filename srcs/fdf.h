/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:53:01 by jmehlig           #+#    #+#             */
/*   Updated: 2022/05/04 21:14:53 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "../minilibx_macos/mlx.h"
# include "../includes/libft/libft.h"
# include "../includes/get_next_line/get_next_line.h"

typedef struct s_iso
{
	int	ix;
	int	iy;
	int	icolor;
}				t_iso;

typedef struct s_points
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
}				t_points;

typedef struct s_bres
{
	int		dx;
	int		dy;
	int		err;
	int		sx;
	int		sy;
	int		doub_err;
}				t_bres;

typedef struct s_data
{
	int			zoom;
	int			z_shift;
	int			x_shift;
	int			y_shift;
	int			***matrix;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_l;
	int			end;
	int			nl;
	int			col;
	t_bres		bresenham;
	t_points	points;
}				t_data;

//fdf.c
int			ft_exit(int keycode, t_data *s);
void		ft_init(t_data *s);
void		my_mlx_matrix_put(t_data *s);
int			ex(void);

//plot.c
void		bresenham(t_iso old_p, t_iso new_p, t_data *s);
void		plot_line(t_iso old_p, t_iso new_p, t_data *s, t_bres b);
int			line_color(t_iso old_p, t_iso new_p, int y);
t_iso		to_isometric(int x, int y, t_data *s);
void		my_mlx_pixel_put(t_data *s, int color, t_points points);

//get_data.c
void		get_data(int fd, t_data *s);
void		ft_make_points(t_data *s, char *str);
void		ft_point_colors(t_data *s, char **columns, int i, int j);
char		*to_str(int fd);
void		error(char *str);

//utils.c
int			get_colnum(char *str);
int			get_newline_num(char *str);
int			hex_to_deci(char *hex);
void		free_matrix(t_data *s);

//move.c
int			keys(int keycode, t_data	*s_in);
int			keycode_check(int keycode);
void		create_new_map(t_data s);

#endif
