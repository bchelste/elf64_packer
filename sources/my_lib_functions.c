/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lib_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:33:24 by bchelste          #+#    #+#             */
/*   Updated: 2023/05/18 22:08:00 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void *my_memset(void *src, int c, size_t len) {
	unsigned char *tmp = (unsigned char *)src;
	unsigned char simbol = (unsigned char)c;
	
	while (len) {
		*tmp = simbol;
		++tmp;
		--len;
	}
	return src;
}

size_t my_strlen(const char *src) {
	size_t nbr = 0;
	
	while (src[nbr] != '\0')
		++nbr;
	return nbr;
}

int my_strcmp(const char *lhs, const char *rhs) {
	while (*lhs || *rhs) {
		if ((unsigned char)*lhs != (unsigned char)*rhs)
			return ((unsigned char)*lhs - (unsigned char)*rhs);
		++lhs;
		++rhs;
	}
	return 0;
}

int my_strncmp(const char *lhs, const char *rhs, size_t nbr) {
	size_t i = 0;
	while ((i < nbr) && (lhs[i] || rhs[i])) {
		if ((unsigned char)lhs[i] != (unsigned char)rhs[i])
			return ((unsigned char)lhs[i] - (unsigned char)rhs[i]);
		++i;
	}
	return 0;
}

int my_memcmp(const void *lhs, const void *rhs, size_t nbr) {
	unsigned char *lhs_ptr = (unsigned char*)lhs;
	unsigned char *rhs_ptr = (unsigned char*)rhs;
	for (size_t i = 0; i < nbr; ++i) {
		if (lhs_ptr[i] != rhs_ptr[i])
			return (lhs_ptr[i] - rhs_ptr[i]);
	}
	return 0;
}

void *my_memmove(void *dst, const void *src, size_t len) {
	if (!dst && !src)
		return NULL;
	unsigned char *dst_ptr = (unsigned char*)dst;
	unsigned char *src_ptr = (unsigned char*)src;
	size_t cntr = 0;
	if (dst > src) {
		while (cntr < len) {
			dst_ptr[(len - 1) - cntr] = src_ptr[(len - 1) - cntr];
			++cntr;
		}
	} else {
		while (len--) {
			dst_ptr[cntr] = src_ptr[cntr];
			++cntr;
		}
	}
	return dst;
}

uint64_t key_generator(size_t len) {
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        write(STDERR_FILENO, ERROR_KEY, my_strlen(ERROR_KEY));
        close(fd);
        return 1;
    }
    long long key = 0;
    if (!read(fd, &key, len)) {
        write(STDERR_FILENO, ERROR_KEY, my_strlen(ERROR_KEY));
        close(fd);
        return 1;
    }
    close(fd);
    return ((uint64_t)key);
}

ssize_t wright_data(int fd, ssize_t size, ssize_t chunk, void *storage) {
    ssize_t i = 0;
    void *tmp_ptr = storage;
    while (i < size) {
        tmp_ptr = storage + i;
        if (size - i >= chunk) {
            i += write(fd, tmp_ptr, chunk);
        } else {
            i += write(fd, tmp_ptr, size % chunk);
        }
    }
    return i;
}