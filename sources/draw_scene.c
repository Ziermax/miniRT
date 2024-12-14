/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 02:09:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/12/03 20:14:26 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector.h"
#include <stdio.h>

void	my_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	int	thck[2];
	int	px[2];

	x *= BPP;
	y *= BPP;
	if (y < 0 || x < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return ;
	thck[X] = 0;
	while (thck[X] < BPP)
	{
		thck[Y] = 0;
		while (thck[Y] < BPP)
		{
			px[X] = x + thck[X];
			px[Y] = y + thck[Y];
			if (px[X] >= 0 && px[X] < W_WIDTH && px[Y] >= 0 && px[Y] < W_HEIGHT)
				mlx_put_pixel(img, x + thck[X], y + thck[Y], color);
			thck[Y]++;
		}
		thck[X]++;
	}
}

t_vector	get_pixel_direction(int x, int y, t_scene scene)
{
	t_vector	pixel;
	t_vector	direction;
	float		dx;
	float		dy;

	dx = (float)x * BPP / W_WIDTH;
	dy = (float)y * BPP / W_HEIGHT;
	pixel.x = (2.f * dx - 1.f) * scene.sim_width;
	pixel.y = (1.f - 2.f * dy) * scene.sim_height;
	pixel.z = 1.f;
	direction.x = pixel.x;
	direction.y = pixel.y;
	direction.z = pixel.z;
	//direction = rotar_vector(direction, scene.camera.orientation);
	return (direction);
}

void	draw_scene(t_data data, t_scene scene)
{
	mlx_image_t		*img;
	unsigned int	x;
	unsigned int	y;
	t_vector		px_direction;
	t_trace			ray;

	img = data.img;
	y = 0;
	while (y < img->height / BPP)
	{
		x = 0;
		while (x < img->width / BPP)
		{
			px_direction = get_pixel_direction(x, y, scene);
			ray = ray_tracing(scene.camera.origin, px_direction,
					scene.objects, scene.lights, scene.ambient_light);
			if (!ray.hit)
				ray.color = 0xff;
				//ray.color = scene.ambient_light.color;
				//ray.color = scene.ambient_light.color;
			my_put_pixel(data.img, x, y, ray.color);
			x++;
		}
		y++;
	}
	//my_put_pixel(data.img, 540 / BPP, 570 / BPP, 0xFFffFFff);
	//my_put_pixel(data.img, 590 / BPP, 620 / BPP, 0xFFffFFff);
}
			//printf("Pixel: (%d, %d)\n", x, y);
			//printf("\n");
