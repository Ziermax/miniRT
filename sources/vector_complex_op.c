/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_complex_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:09:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/04 23:09:21 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/vector.h"
#include <math.h>

float	distance_of_points(t_vector vec1, t_vector vec2)
{
	float	x;
	float	y;
	float	z;

	x = vec1.x - vec2.x;
	y = vec1.y - vec2.y;
	z = vec1.z - vec2.z;
	return (sqrtf(x * x + y * y + z * z));
}

float	angle_between_vectors(t_vector vec1, t_vector vec2)
{
	float	quotient;
	float	divident;

	divident = sqrtf(dot_product(vec1, vec1) * dot_product(vec2, vec2));
	if (!divident)
		return (M_PI_2);
	quotient = dot_product(vec1, vec2);
	return (acosf(quotient / divident));
}
