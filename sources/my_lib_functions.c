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