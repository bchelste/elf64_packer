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

int parser_file_info(t_woody *woody) {
    if (check_file_format(woody->ptr)) {
        free(woody->ptr);
        return 1;
    }

    return 0;
}