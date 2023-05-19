/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_copy.c                                        :+:      :+:    :+:   */
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

int get_file_size(int fd, t_woody *woody) {
    woody->file_size = lseek(fd, 0, SEEK_END);
    if ((woody->file_size < 0) || (lseek(fd, 0, SEEK_SET))) {
        return 1;
    }
    if (woody->file_size < (long)(sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + sizeof(Elf64_Shdr)))
        return 1;
    return 0;
}

int read_file(int fd, t_woody *woody) {
	woody->ptr = malloc(woody->file_size);
	if (woody->ptr == NULL) {
		write(STDERR_FILENO, MALLOC_ERROR, my_strlen(MALLOC_ERROR));
		close(fd);
		return 1;
	}
	if (read(fd, woody->ptr, woody->file_size) != woody->file_size) {
		free(woody->ptr);
		write(STDERR_FILENO, READ_ERROR, my_strlen(READ_ERROR));
		close(fd);
		return 1;
	}
	close(fd);
	return(0);
}

int copy_file(const char *file_path, t_woody *woody) {
	int fd = open(file_path, O_RDONLY);
	if (fd == -1) {
		write(STDERR_FILENO, F_OPEN_ERROR, my_strlen(F_OPEN_ERROR));
		return -1;
	}
	if (get_file_size(fd, woody)) {
		write(STDERR_FILENO, INVALID_ELF, my_strlen(INVALID_ELF));
		return 1;
	}
	if (read_file(fd, woody))
		return 1;
	return 0;
}
