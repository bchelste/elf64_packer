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

int set_crypto_data(t_crypto *crypto, t_woody *woody) {
    if ((crypto->key = key_generator(KEY_LEN)) == 1)
        return 1;
    woody->key = crypto->key;
    crypto->original_entry = woody->header->e_entry;
    crypto->encrypted_code = woody->text_section->sh_addr;
    crypto->encrypted_size = woody->text_section->sh_size;
    Elf64_Ehdr *tmp = (Elf64_Ehdr*)woody->ptr;
    tmp->e_entry = woody->code_segment->p_vaddr + woody->code_segment->p_memsz;
    crypto->encrypted_entry = tmp->e_entry;
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
    printf("%skey_value: %#.16llx\n%s", YELLOW, (long long)tmp_key, RESET);
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
        i = wright_data(fd, woody->file_size, BUFFER_SIZE, woody->ptr);
        close(fd);
        printf("%sFile create: woody\n%s", GREEN, RESET);
    } else { 
        return -1;
    }
    return (i == woody->file_size);
}

int make_magic(t_woody *woody, t_crypto *crypto) {
    void *pos = woody->ptr + woody->text_section->sh_offset;
    encrypt_text_section(woody->text_section->sh_size, pos, crypto->key);
    change_load_segment(crypto, woody);
    if (write_to_file(woody) != 1){
        output_error(E_WRITE_WOODY);
        return 1;
    }
    return 0;
}

int encrypt_file(t_woody *woody) {
    t_crypto crypto;
    my_memset(&crypto, 0, sizeof(crypto));
    if (set_crypto_data(&crypto, woody))
        return 1;
    if (make_magic(woody, &crypto))
        return 1;
    return 0;
}
