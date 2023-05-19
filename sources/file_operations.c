/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:33:24 by bchelste          #+#    #+#             */
/*   Updated: 2023/05/18 22:08:00 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

ssize_t get_file_size(FILE *in_file) {
    ssize_t result = 0;
    fseek(in_file, 0, SEEK_END);
    result = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);
    return result;
}