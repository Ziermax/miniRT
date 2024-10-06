/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 02:10:12 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/10/04 11:36:44 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structs.h"

void	draw_scene(t_data data, t_scene scene);
t_trace	sphere_intersection(t_vector point, t_vector direction, t_object *obj);
t_trace	ray_tracing(t_vector point,
			t_vector direction, t_object *object, t_light *lights);

#endif
