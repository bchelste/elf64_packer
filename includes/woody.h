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

#include "defines.h"

# define BUFFER_SIZE	4096
# define KEY_LEN		8

extern unsigned char	g_decryptor[];
extern unsigned int		g_decryptor_len;

typedef struct s_woody {
	char		flag_info;
	ssize_t 	file_size;
	void 		*ptr;
	Elf64_Ehdr	*header;
	Elf64_Phdr	*segments;
	Elf64_Phdr	*code_segment;
	Elf64_Shdr	*sections;
	Elf64_Shdr	*text_section;
	uint64_t	key;
} t_woody;

typedef struct s_crypto {
	uint64_t	original_entry;
	uint64_t	encrypted_code;
	uint64_t	encrypted_size;
	uint64_t	key;
	uint64_t	encrypted_entry;
} t_crypto;

int copy_file(const char *file_path, t_woody *woody);
int parser_file_info(t_woody *woody);
int encrypt_file(t_woody *woody);

void *my_memset(void *src, int c, size_t len);
size_t my_strlen(const char *src);
int my_strcmp(const char *lhs, const char *rhs);
int my_strncmp(const char *lhs, const char *rhs, size_t nbr);
int my_memcmp(const void *lhs, const void *rhs, size_t nbr);
void *my_memmove(void *dst, const void *src, size_t len);
uint64_t key_generator(size_t len);
ssize_t wright_data(int fd, ssize_t size, ssize_t chunk, void *storage);
ssize_t output_error(const char *src);

#endif