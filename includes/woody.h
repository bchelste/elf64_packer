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

# include <unistd.h>

typedef struct s_woody {
	ssize_t filesize;
	void 	*ptr;
	char	flag_info;
	
	
} t_woody;

int cl_arg_parser(int argc, char **argv, t_woody *woody);

void *my_memset(void *src, int c, size_t len);
size_t my_strlen(const char *src);
int my_strcmp(const char *lhs, const char *rhs);

#endif