/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_tracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:17:54 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/05 20:22:56 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "../Libft/includes/libft.h"
#include "../includes/vector.h"
#include "../includes/ray_tracing.h"

float	straight_angle_percentage(float angle)
{
	float	percentage;

	if (angle >= M_PI_2 && angle <= M_PI_2 + M_PI)
	{
		if (angle <= M_PI)
			percentage = (angle - M_PI_2) / M_PI_2;
		else
			percentage = (M_PI_2 - (angle - M_PI)) / M_PI_2;
	}
	else
		percentage = 0.f;
	return (percentage);
}

int	asign_color_intensity(int color, float percentage, int ambient)
{
	int	new_percent;

	new_percent = percentage * COLOR_DEF;
	color = proportional_color(new_percent, ambient, color);
	return (color);
}

int	light_obstruction(t_vector point, t_vector direction,
		t_object *object, t_trace ray)
{
	t_trace	light_ray;
	float	distance;

	distance = distance_of_points(point, ray.hit_point);
	while (object)
	{
		if (object == ray.object)
		{
			object = object->next;
			continue ;
		}
		light_ray = hit_tracer(point, direction, object);
		if (light_ray.hit)
		{
			light_ray.distance = distance_of_points(point, light_ray.hit_point);
			if (light_ray.distance <= distance)
				return (1);
		}
		object = object->next;
	}
	return (0);
}

t_vector	object_normal(t_vector point, t_object *object)
{
	t_vector	normal;

	ft_bzero(&normal, sizeof(t_vector));
	if (object->type == SPHERE)
		normal = sphere_normal(point, object);
	else if (object->type == PLANE)
		normal = plane_normal(point, object);
	else if (object->type == CYLINDER)
		normal.y = 0;
	else
		normal.z = 0;
	return (normal);
}

int	get_color_from_object(t_trace ray, t_light *light, t_object *objects)
{
	t_vector	normal;
	t_vector	light_direction;
	int			color;
	float		rangle;
	float		percentage;

	percentage = 0.f;
	normal = object_normal(ray.hit_point, ray.object);
	while (light)
	{
		light_direction = add_vec(ray.hit_point, light->origin, -1);
		if (!light_obstruction(light->origin, light_direction, objects, ray))
		{
			rangle = angle_between_vectors(light_direction, normal);
			percentage += straight_angle_percentage(rangle);
		//	printf("percentage: %f\n", percentage);
		}
		//else
		//	printf("Obstructed\n");
		light = light->next;
	}
	if (percentage > 1.f)
		percentage = 1.f;
	color = asign_color_intensity(ray.object->color, percentage, 0xff);
	return (color);
}
//	if (ray.object->type == SPHERE)
//		normal = sphere_normal(ray.hit_point, ray.object);
//	else if (ray.object->type == PLANE)
//		normal.x = 0;
//	else if (ray.object->type == CYLINDER)
//		normal.y = 0;
//	else
//		normal.z = 0;
