/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:30 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/04 11:10:26 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"
#include <math.h>

t_vector	add_vec(t_vector vec1, t_vector vec2, int sign)
{
	if (sign >= 0)
		sign = 1;
	else
		sign = -1;
	vec1.x = vec1.x + sign * vec2.x;
	vec1.y = vec1.y + sign * vec2.y;
	vec1.z = vec1.z + sign * vec2.z;
	return (vec1);
}

t_vector	scl_vec(t_vector vec, float scale)
{
	vec.x = vec.x * scale;
	vec.y = vec.y * scale;
	vec.z = vec.z * scale;
	return (vec);
}

float	dot_product(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vector	vec_x_mat(t_vector vec, t_matrix mat)
{
	t_vector	result;

	result.x = vec.x * mat.vecx.x + vec.y * mat.vecy.x + vec.z * mat.vecz.x;
	result.y = vec.x * mat.vecx.y + vec.y * mat.vecy.y + vec.z * mat.vecz.y;
	result.z = vec.x * mat.vecx.z + vec.y * mat.vecy.z + vec.z * mat.vecz.z;
	return (result);
}
