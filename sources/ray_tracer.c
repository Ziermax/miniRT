/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:17:02 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/04 23:11:08 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ray_tracing.h"
#include "../includes/vector.h"

t_trace	hit_tracer(t_vector point, t_vector direction, t_object *object)
{
	t_trace		ray;

	if (object->type == SPHERE)
		ray = sphere_intersection(point, direction, object);
	else if (object->type == PLANE)
		ray = plane_intersection(point, direction, object);
	else if (object->type == CYLINDER)
		ray.hit = 0;
	else
		ray.hit = 0;
	return (ray);
}
//	ray.distance = distance_of_points(point, ray.hit_point);

t_trace	ray_tracing(t_vector point, t_vector direction,
		t_object *object, t_light *lights)
{
	t_trace		ray;
	t_trace		aux;
	t_object	*obj_lst;

	ray.distance = 2147483647.f;
	ray.hit = 0;
	obj_lst = object;
	while (object)
	{
		aux = hit_tracer(point, direction, object);
		aux.object = object;
		object = object->next;
		if (!aux.hit)
			continue ;
		aux.distance = distance_of_points(point, aux.hit_point);
		if (aux.distance < ray.distance)
			ray = aux;
	}
	if (!ray.hit)
		return (ray);
	ray.color = get_color_from_object(ray, lights, obj_lst);
	return (ray);
}
