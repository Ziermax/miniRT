/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:45:16 by avolcy            #+#    #+#             */
/*   Updated: 2024/10/05 20:22:38 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Libft/includes/libft.h"
#include "../includes/miniRT.h"

void	key_events(void *param)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = ((t_data *)param)->mlx;
	image = ((t_data *)param)->img;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

t_object	*hardcode_plane(void)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->type = PLANE;
	object->shape.plane.center.x = 0.f;
	object->shape.plane.center.z = 0.f;
	object->shape.plane.center.y = -2.f;
	object->shape.plane.normal.x = 0.f;
	object->shape.plane.normal.z = 0.f;
	object->shape.plane.normal.y = 1.f;
	object->color = 0xFF0000ff;
	object->next = NULL;
	return (object);
}

t_object	*hardcode_sphere(void)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->type = SPHERE;
	object->shape.sphere.center.x = 0.f;
	object->shape.sphere.center.z = 20.f;
	object->shape.sphere.center.y = 0.f;
	object->shape.sphere.radius = 5.f;
	object->color = 0x00FF00ff;
	object->next = NULL;
	return (object);
}

t_light	*hardcode_light(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin.x = 0.f;
	light->origin.z = 0.f;
	light->origin.y = 0.f;
	light->color = 0xffFF;
	light->brightness = 1.f;
	light->next = NULL;
	return (light);
}

t_scene	init_scene(void)
{
	t_scene	scene;

	/*	*
	 *	Camara
	 */
	scene.camera.origin.x = 0.f;
	scene.camera.origin.y = 0.f;
	scene.camera.origin.z = 0.f;
	scene.camera.orientation.x = 0.f;
	scene.camera.orientation.y = 0.f;
	scene.camera.orientation.z = 1.f;
	scene.camera.fov_h = 70;
	scene.camera.fov_v = (float)scene.camera.fov_h * W_WIDTH / W_HEIGHT;
	/*	*
	 *	Luces
	 */
	scene.ambient_light.brightness = 1.f;
	scene.ambient_light.color = 0x0;
	scene.light_count = 1;
	scene.lights = NULL;
	lst_add_back(&scene.lights, hardcode_light());
	scene.lights->origin.x = -10;
	scene.lights->origin.y = 5.f;
	scene.lights->origin.z = 15;
	lst_add_back(&scene.lights, hardcode_light());
	/*	*
	 *	Objects
	 */
	scene.object_count = 1;
	scene.objects = NULL;
	//scene.objects->shape.sphere.center.x = 2.f;
	//scene.objects->shape.sphere.center.y = 4.f;
	//scene.objects->color = 0x00FF00ff;
	//scene.objects->shape.sphere.center.z = 15.f;
	lst_add_back(&scene.objects, hardcode_plane());
	scene.objects->shape.plane.normal.z = 0.f;
	scene.objects->shape.plane.center.y = -5.f;
	scene.objects->color = 0xFFff;
	lst_add_back(&scene.objects, hardcode_plane());
	scene.objects->next->shape.plane.center.z = 25.f;
	scene.objects->next->shape.plane.normal.y = 0.f;
	scene.objects->next->shape.plane.normal.z = -1.f;
	lst_add_back(&scene.objects, hardcode_sphere());
	scene.sim_height = tan(scene.camera.fov_v * M_PI / 180.f / 2.f);
	scene.sim_width = -tan(scene.camera.fov_h * M_PI / 180.f / 2.f);
	return (scene);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)data;
	data.mlx = mlx_init(W_WIDTH, W_HEIGHT, "miniRT", true);
	data.img = mlx_new_image(data.mlx, W_WIDTH, W_HEIGHT);
	data.scene = init_scene();
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop_hook(data.mlx, key_events, &data.mlx);
	draw_scene(data, data.scene);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
