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

void output_info(t_woody *woody) {
	write (STDOUT_FILENO, "output logs\n", 13);
	if (woody->fd_logs > 0)
		close(woody->fd_logs);
}

int cl_arg_check(int argc, char **argv, t_woody *woody) {
	if ((argc != 2) && (argc != 3)) {
		write(STDERR_FILENO, ARGS_ERROR, my_strlen(ARGS_ERROR));
		return 1;
	}
	if (argc == 3) {
		if (!my_strcmp(argv[1], "-i")) {
			woody->flag_info = 'i';
			woody->fd_logs = open("logfile.txt", O_WRONLY|O_TRUNC|O_CREAT);
			if (woody->fd_logs < 0) {
				woody->flag_info = 0;
				write(STDERR_FILENO, LOG_FD_ER, my_strlen(LOG_FD_ER));
			}
		} else {
			write(STDERR_FILENO, WRONG_FLAG, my_strlen(WRONG_FLAG));
			return 1;
		}
	}
	return 0;
}

int woody_action(const char *file_path, t_woody *woody) {
	if (copy_file(file_path, woody))
		return 1;
	if (parser_file_info(woody))
		return 1;
	if (encrypt_file(woody))
		return 1;
	if (woody->flag_info == 'i')
		output_info(woody);
	if (woody->ptr != NULL)
		free(woody->ptr);
	return 0;
}

int	main(int argc, char **argv) {
	
	t_woody woody;
	my_memset(&woody, 0, sizeof(woody));
	
	if (cl_arg_check(argc,argv, &woody))
		return 1;
	if (woody_action(argv[argc - 1], &woody)) {
		if (woody.ptr != NULL)
			free(woody.ptr);
		return 1;
	}
	return 0;
}