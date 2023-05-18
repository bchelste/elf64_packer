/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:54:20 by bchelste          #+#    #+#             */
/*   Updated: 2023/05/18 22:45:45 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int cl_arg_check(int argc, char **argv, t_woody *woody) {
	if ((argc != 2) && (argc != 3)) {
		write(STDERR_FILENO, ARGS_ERROR, my_strlen(ARGS_ERROR));
		return 1;
	}
	if (argc == 3) {
		if (!my_strcmp(argv[1], "-i")) {
			woody->flag_info = 'i';
		} else {
			write(STDERR_FILENO, WRONG_FLAG, my_strlen(WRONG_FLAG));
			return 1;
		}
	}
	return 0;
}

int cl_arg_parser(int argc, char **argv, t_woody *woody) {
	if (cl_arg_check(argc, argv, woody))
		return 1;
		
	return 0;
}