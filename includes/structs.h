/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:12:42 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/05 20:23:38 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define W_WIDTH	1000
# define W_HEIGHT	1000
# define ANG_PRES 1000
# define COLOR_DEF 1000
# define BPP 10
# define X 0
# define Y 1

typedef enum e_objtype
{
	SPHERE,
	PLANE,
	CYLINDER,
	PARABOLOID
}	t_objtype;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_matrix
{
	t_vector	vecx;
	t_vector	vecy;
	t_vector	vecz;
}	t_matrix;

typedef struct s_sline
{
	t_vector	point;
	t_vector	direction;
}	t_sline;

typedef struct s_sphere
{
	t_vector	center;
	float		radius;
}	t_sphere;

typedef struct s_plane
{
	t_vector	center;
	t_vector	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	axis;
	float		radius;
	float		height;
}	t_cylinder;

typedef struct s_paraboloid
{
	t_vector	center;
	t_vector	direction;
	float		radius;
	int			color;
}	t_paraboloid;

typedef struct s_light	t_light;

struct s_light
{
	t_light		*next;
	t_vector	origin;
	float		brightness;
	int			color;
};

typedef struct s_camera
{
	t_vector	origin;
	t_vector	orientation;
	int			fov_h;
	float		fov_v;
}	t_camera;

typedef union u_shape
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_shape;

typedef struct s_object	t_object;

struct s_object
{
	t_object	*next;
	t_objtype	type;
	t_shape		shape;
	int			color;
};

typedef struct s_ambient
{
	float		brightness;
	int			color;
}	t_ambient;

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient_light;
	t_light		*lights;
	t_object	*objects;
	int			light_count;
	int			object_count;
	float		sim_height;
	float		sim_width;
}	t_scene;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
}	t_data;

typedef struct s_trace
{
	char		hit;
	t_vector	hit_point;
	float		distance;
	int			color;
	t_object	*object;
}	t_trace;

typedef struct s_anal_trace
{
	float		lambda;
	float		discriminant;
	t_vector	diff_x;
	float		a;
	float		half_b;
	float		c;
}	t_anal_trace;

void	print_vector(t_vector vector);
char	*get_obj_type(t_objtype type);

#endif
