/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:15:16 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/04 22:15:25 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "../includes/vector.h"

static float	get_lambda_half_b(t_anal_trace data)
{
	float	lambda1;
	float	lambda2;
	float	discriminant_sqrted;

	if (data.discriminant < 0)
		return (0.f);
	data.half_b = -data.half_b;
	if (data.discriminant == 0)
		return (data.half_b / data.a);
	discriminant_sqrted = sqrtf(data.discriminant);
	lambda1 = (data.half_b + discriminant_sqrted) / data.a;
	lambda2 = (data.half_b - discriminant_sqrted) / data.a;
	if (lambda1 < lambda2 && lambda1 >= 0)
		return (lambda1);
	return (lambda2);
}

t_trace	sphere_intersection(t_vector point, t_vector direction, t_object *obj)
{
	t_anal_trace	dt;
	t_trace			ray;

	ray.hit = 0;
	dt.diff_x = add_vec(point, obj->shape.sphere.center, -1);
	dt.a = dot_product(direction, direction);
	dt.half_b = dot_product(dt.diff_x, direction);
	dt.c = dot_product(dt.diff_x, dt.diff_x) - pow(obj->shape.sphere.radius, 2);
	dt.discriminant = pow(dt.half_b, 2) - dt.a * dt.c;
	if (dt.discriminant < 0)
		return (ray);
	dt.lambda = get_lambda_half_b(dt);
	if (dt.lambda < 0)
		return (ray);
	ray.hit = 1;
	ray.hit_point = add_vec(point, scl_vec(direction, dt.lambda), 1);
	return (ray);
}

t_trace	plane_intersection(t_vector point, t_vector direction, t_object *obj)
{
	t_trace		ray;
	t_vector	diff_x;
	float		quotient;
	float		divident;
	float		lambda;

	ray.hit = 0;
	diff_x = add_vec(point, obj->shape.plane.center, -1);
	divident = dot_product(direction, obj->shape.plane.normal);
	if (!divident)
		return (ray);
	quotient = -dot_product(diff_x, obj->shape.plane.normal);
	lambda = quotient / divident;
	if (lambda < 0)
		return (ray);
	ray.hit = 1;
	ray.hit_point = add_vec(point, scl_vec(direction, lambda), 1);
	return (ray);
}
