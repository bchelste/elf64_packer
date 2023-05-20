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

uint64_t	set_current_entry(t_woody *woody) {
    Elf64_Ehdr *tmp = (Elf64_Ehdr*)woody->ptr;
    tmp->e_entry = woody->code_segment->p_vaddr + woody->code_segment->p_memsz;
    return tmp->e_entry;
}

int set_crypto_data(t_crypto *crypto, t_woody *woody) {
    if ((crypto->key = key_generator(KEY_LEN)) == 1)
        return 1;
    crypto->original_entry = woody->header->e_entry;
    crypto->encrypted_code_section = woody->text_section->sh_addr;
    crypto->encrypted_size = woody->text_section->sh_size;
    crypto->encrypted_entry = set_current_entry(woody);
    return 0;
}

void encrypt_text_section(size_t size, void *data, uint64_t key) {
    uint64_t tmp_key = key;
    uint64_t value;
    for (size_t i = 0; i < size; ++i) {
        *(unsigned char*)(data + i) = *(unsigned char *)(data + i) ^ (key & 0b11111111);
        value = key & 0b0000001;
        value <<= 63;
        key = (key >> 1) | value;
    }
    printf("key_value: %#.16llx\n", (long long)tmp_key);
}

void change_load_segment(t_crypto *crypto, t_woody *woody) {
    void *tmp_ptr = woody->ptr + woody->code_segment->p_offset + woody->code_segment->p_filesz;
    woody->code_segment->p_memsz += g_decryptor_len;
    woody->code_segment->p_filesz += g_decryptor_len;
    woody->code_segment->p_flags = woody->code_segment->p_flags | PF_W;
    ssize_t len = g_decryptor_len - sizeof(t_crypto);
    my_memmove(tmp_ptr, g_decryptor, len);
    my_memmove(tmp_ptr + len, crypto, sizeof(t_crypto));
}

int write_to_file(t_woody *woody) {
    int fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 0755);
    ssize_t i = 0;
    if (fd > 0) {
        for (; i < woody->file_size; ++i)
            write(fd, woody->ptr + i, 1);
        close(fd);
        printf("File create: woody\n");
    } else { 
        return 0;
    }
    return (i == woody->file_size);
}

int encrypt_file(t_woody *woody) {
    t_crypto crypto;
    void *pos = woody->ptr + woody->text_section->sh_offset;
    if (set_crypto_data(&crypto, woody)) {
        free(woody->ptr);
        return 1;
    }
    encrypt_text_section(woody->text_section->sh_size, pos, crypto.key);
    change_load_segment(&crypto, woody);
    if (write_to_file(woody) != 1){
        write(STDERR_FILENO, E_WRITE_WOODY, my_strlen(E_WRITE_WOODY));
        return 1;
    }
    return 0;
}
