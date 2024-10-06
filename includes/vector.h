/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:47:20 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/01 15:58:17 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "structs.h"

t_vector	add_vec(t_vector vec1, t_vector vec2, int sign);
t_vector	scl_vec(t_vector vec, float scale);
float		dot_product(t_vector vec1, t_vector vec2);
t_vector	vec_x_mat(t_vector vec, t_matrix mat);
float		distance_of_points(t_vector vec1, t_vector vec2);
float		angle_between_vectors(t_vector vec1, t_vector vec2);

#endif
