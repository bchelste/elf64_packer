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
	unsigned char *src = woody->ptr;
	printf("%s---------------------------------\n%s", BLUE, RESET);
	printf("%s        WOODY INFO OUTPUT        \n%s", BLUE, RESET);
	printf("%s---------------------------------\n%s", BLUE, RESET);
	printf("%sfile size: %ld\n%s", BLUE, woody->file_size, RESET);
	printf("%sfile extension : %x -> %c%c%c\n%s", BLUE, src[0], src[1], src[2], src[3], RESET);
	printf("%self class: %d (01 - elf32, and 02 - elf64)\n%s", BLUE, src[4], RESET);
	printf("%sfile type: %d (2 - EXEC, and 3 - DYN)\n%s", BLUE, src[16], RESET);
	printf("%sfile architect: %d (62 -> EM_X86_64)\n%s", BLUE, src[18], RESET);
	printf("%s---------------------------------\n%s", BLUE, RESET);
}

int cl_arg_check(int argc, char **argv, t_woody *woody) {
	if ((argc != 2) && (argc != 3)) {
		output_error(E_ARGS);
		return 1;
	}
	if (argc == 3) {
		if (!my_strcmp(argv[1], "-i")) {
			woody->flag_info = 'i';
		} else {
			output_error(E_WRONG_FLAG);
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