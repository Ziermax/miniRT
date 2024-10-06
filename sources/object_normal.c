/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:19:06 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/04 20:32:34 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	sphere_normal(t_vector point, t_object *object)
{
	t_vector	normal;

	normal = add_vec(point, object->shape.sphere.center, -1);
	return (normal);
}

t_vector	plane_normal(t_vector point, t_object *object)
{
	(void)point;
	return (object->shape.plane.normal);
}
