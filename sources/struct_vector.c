/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:23:39 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/09/30 13:46:36 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/structs.h"
#include "../Libft/includes/libft.h"

void	print_vector(t_vector vector)
{
	printf("(%.2f, %.2f, %.2f)\n", vector.x, vector.y, vector.z);
}

char	*get_obj_type(t_objtype type)
{
	if (type == SPHERE)
		return ("SPHERE");
	if (type == PLANE)
		return ("PLANE");
	if (type == CYLINDER)
		return ("CYLINDER");
	if (type == PARABOLOID)
		return ("PARABOLOID");
	return ("No type");
}
