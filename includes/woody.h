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

# include <unistd.h>
# include <stdio.h>
# include <elf.h>
# include <stdlib.h>
# include <fcntl.h>

# define ARGS_ERROR		"Wrong syntax. Correct way is to type: ./woody_woodpacker ./path/binary or ./woody_woodpacker -i ./path/binary\n"
# define WRONG_FLAG		"Only -i flag is managed (wrong flag would be ignored)\n"
# define LOG_FD_ER		"There was something wrong with log file fd\n"
# define F_OPEN_ERROR	"failed -> open input file\n"
# define INVALID_ELF	"Error: invalid file, it must be valid linux ELF_64\n"
# define MALLOC_ERROR	"Error: something wrong with malloc\n"
# define READ_ERROR		"Error: something wrong with reading file\n"
# define ENCRYPTED		"Binary file has already encrypted\n"
# define NOSPACE		"There is no empty space fo decryptor\n"
# define ERROR_KEY		"TSomething wrong with /dev/urandom fd\n"
# define E_WRITE_WOODY	"Error: could not write to 'woody' file\n"

# define BUFFER_SIZE	4096
# define KEY_LEN		8

extern unsigned char	g_decryptor[];
extern unsigned int		g_decryptor_len;

typedef struct s_woody {
	char		flag_info;
	int			fd_logs;
	ssize_t 	file_size;
	void 		*ptr;
	Elf64_Ehdr	*header;
	Elf64_Phdr	*segments;
	Elf64_Phdr	*code_segment;
	Elf64_Shdr	*sections;
	Elf64_Shdr	*text_section;
} t_woody;

typedef struct s_crypto {
	uint64_t	key;
	uint64_t	original_entry;
	uint64_t	encrypted_entry;
	uint64_t	encrypted_code_section;
	uint64_t	encrypted_size;
} t_crypto;

int cl_arg_check(int argc, char **argv, t_woody *woody);
int get_file_size(int fd, t_woody *woody);
int read_file(int fd, t_woody *woody);
int copy_file(const char *file_path, t_woody *woody);

int check_file_format(unsigned char *src);
Elf64_Phdr	*get_load_segment(t_woody *woody);
Elf64_Shdr	*get_text_section(t_woody *woody);
void set_segments(t_woody *woody);
int parser_file_info(t_woody *woody);

int encrypt_file(t_woody *woody);

void *my_memset(void *src, int c, size_t len);
size_t my_strlen(const char *src);
int my_strcmp(const char *lhs, const char *rhs);
int my_strncmp(const char *lhs, const char *rhs, size_t nbr);
int my_memcmp(const void *lhs, const void *rhs, size_t nbr);
void *my_memmove(void *dst, const void *src, size_t len);

#endif