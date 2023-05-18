/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:53:50 by bchelste          #+#    #+#             */
/*   Updated: 2023/05/18 20:55:05 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int	main(int argc, char **argv) {
	
	t_woody woody;
	my_memset(&woody, 0, sizeof(woody));
	
	if (cl_arg_parser(argc,argv, &woody))
		return 1;
	
	return 0;
}