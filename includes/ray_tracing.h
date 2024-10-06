/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:28:04 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/04 20:32:04 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# include "structs.h"

t_trace		hit_tracer(t_vector point, t_vector direction, t_object *object);
/*light functions */
t_vector	sphere_normal(t_vector point, t_object *object);
t_vector	plane_normal(t_vector point, t_object *object);
int			proportional_color(int percentage, int min_color, int max_color);
t_trace		hit_tracer(t_vector point, t_vector direction, t_object *object);
/*ray functions */
t_trace		sphere_intersection(t_vector point,
				t_vector direction, t_object *obj);
t_trace		plane_intersection(t_vector point,
				t_vector direction, t_object *obj);
int			get_color_from_object(t_trace ray,
				t_light *light, t_object *objects);

#endif
