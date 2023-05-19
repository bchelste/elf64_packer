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
	int ec = 0;
	
	if ((ec = cl_arg_check(argc,argv, &woody)))
		return ec;
	if ((ec = copy_file(argv[argc - 1], &woody)))
		return ec;
	if ((ec = parser_file_info(&woody)))
		return ec;
	
	
	return 0;
}