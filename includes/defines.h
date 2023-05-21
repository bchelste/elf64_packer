#ifndef DEFINES_H
# define DEFINES_H

# define RESET          "\033[0m"
# define RED            "\033[1;31m"
# define YELLOW         "\033[1;33m"
# define BLUE           "\033[1;34m"
# define GREEN          "\033[1;32m"

# define E_ARGS		    "Wrong syntax. Correct way is to type: ./woody_woodpacker ./path/binary or ./woody_woodpacker -i ./path/binary\n"
# define E_WRONG_FLAG	"Only -i flag is managed (wrong flag would be ignored)\n"
# define E_OPEN_FILE	"Failed -> open input file\n"
# define E_INVALID_ELF	"Invalid elf file, it must be valid linux ELF_64\n"
# define E_MALLOC       "Something wrong with malloc\n"
# define E_READ		    "Something wrong with reading file\n"
# define E_ENCRYPTED	"Binary file has already encrypted\n"
# define E_NOSPACE		"There is no empty space fo decryptor\n"
# define E_KEY		    "Something wrong with /dev/urandom fd\n"
# define E_WRITE_WOODY	"It is impossible to write in 'woody' file\n"

#endif