/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:53:41 by bchelste          #+#    #+#             */
/*   Updated: 2023/05/18 22:19:22 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# define ARGS_ERROR		"Wrong syntax. Correct way is to type: ./woody_woodpacker ./path/binary or ./woody_woodpacker -i ./path/binary\n"
# define WRONG_FLAG		"Error: wrong flag!\n"
# define F_OPEN_ERROR	"Error: failed -> open input file\n"
# define INVALID_ELF	"Error: invalid file, it must be valid linux ELF_64\n"
# define MALLOC_ERROR	"Error: something wrong with malloc\n"
# define READ_ERROR		"Error: something wrong with reading file\n"

# define BUFFER_SIZE	4096

# include <unistd.h>
# include <stdio.h>
# include <elf.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_woody {
	ssize_t 	file_size;
	void 		*ptr;
	char		flag_info;
	Elf64_Ehdr	*header;
	Elf64_Phdr	*segments;
	Elf64_Phdr	*code_segment;
	Elf64_Shdr	*sections;
	Elf64_Shdr	*text_section;
	
} t_woody;

int cl_arg_check(int argc, char **argv, t_woody *woody);
int get_file_size(int fd, t_woody *woody);
int read_file(int fd, t_woody *woody);
int copy_file(const char *file_path, t_woody *woody);

int check_file_format(unsigned char *src);
Elf64_Phdr	*get_load_segment(t_woody *woody);
Elf64_Shdr	*get_text_section(t_woody *woody);
void set_segments(t_woody *woody);
int parser_file_info(t_woody *woody);

void *my_memset(void *src, int c, size_t len);
size_t my_strlen(const char *src);
int my_strcmp(const char *lhs, const char *rhs);
int my_strncmp(const char *lhs, const char *rhs, size_t nbr);

#endif