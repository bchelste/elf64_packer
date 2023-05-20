#include "woody.h"

int check_file_format(unsigned char *src) {
    if ((src[0] == 0x7f) &&
        (src[1] == 'E') && (src[2] == 'L') && (src[3] == 'F') &&
        (src[4] == ELFCLASS64) &&
        ((src[16] == ET_EXEC) || (src[16] == ET_DYN)) &&
        (src[18] == EM_X86_64)) {
            return 0;
    }
    write(STDERR_FILENO, INVALID_ELF, my_strlen(INVALID_ELF));
    return 1;
}
Elf64_Phdr	*get_load_segment(t_woody *woody) {
    if ((!woody->header->e_phoff) || (!woody->header->e_phnum))
		return (NULL);
    for (int i = 0; i < woody->header->e_phnum; ++i) {
        if ((woody->segments[i].p_type == PT_LOAD) &&
            (woody->segments[i].p_vaddr <= woody->header->e_entry) &&
            (woody->segments[i].p_vaddr + woody->segments[i].p_memsz > woody->header->e_entry) &&
            (woody->segments[i].p_vaddr == woody->segments[i].p_paddr) &&
            (woody->segments[i].p_memsz == woody->segments[i].p_filesz))
                return (&woody->segments[i]);
    }
    return (NULL);
}

Elf64_Shdr	*get_text_section(t_woody *woody) {
    if (!woody->header->e_shoff || !woody->header->e_shnum ||
		(woody->header->e_shstrndx >= woody->header->e_shnum))
		    return (NULL);
    char *sections_names_ptr = (char *)woody->ptr + woody->sections[woody->header->e_shstrndx].sh_offset;
    for (int i = 0; i < woody->header->e_shnum; ++i) {
        if (my_strncmp(".text", sections_names_ptr + woody->sections[i].sh_name, 6) == 0 &&
            (woody->sections[i].sh_type == SHT_PROGBITS) &&
			(woody->sections[i].sh_flags & SHF_EXECINSTR))
			    return (&woody->sections[i]);
    }
    return (NULL);
}

void set_segments(t_woody *woody) {
    woody->header = (Elf64_Ehdr*)woody->ptr;
    woody->segments = (Elf64_Phdr *)(woody->ptr + woody->header->e_phoff);
	woody->sections = (Elf64_Shdr *)(woody->ptr + woody->header->e_shoff);
    woody->code_segment = get_load_segment(woody);
	woody->text_section = get_text_section(woody);
}

int check_encryption(t_woody *woody) {
    void *tmp = woody->ptr + woody->code_segment->p_offset + woody->code_segment->p_filesz - g_decryptor_len;
    if (my_memcmp(tmp, g_decryptor, (size_t)(g_decryptor_len - sizeof(t_crypto))) == 0) {
        write(STDERR_FILENO, ENCRYPTED, my_strlen(ENCRYPTED));
        return 1;
    }
    return 0;
}

int check_empty_space(t_woody *woody) {
    void *tmp = woody->ptr + woody->code_segment->p_offset + woody->code_segment->p_filesz;
    void *pos = tmp;
    while ((pos < (woody->ptr + woody->file_size)) &&
        (*((unsigned char*)pos) == 0)) {
            ++pos;
    }
    if ((pos - tmp) < g_decryptor_len) {
        write(STDERR_FILENO, NOSPACE, my_strlen(NOSPACE));
        return 1;
    }
    return 0;
}

int parser_file_info(t_woody *woody) {
    if (check_file_format(woody->ptr)) {
        free(woody->ptr);
        return 1;
    }
    set_segments(woody);
    if (check_encryption(woody)) {
        free(woody->ptr);
        return 1;
    }
    if (check_empty_space(woody)) {
        free(woody->ptr);
        return 1;
    }
    return 0;
}