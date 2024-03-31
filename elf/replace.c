#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceValues(FILE *file, Elf32_Ehdr header, Elf32_Shdr section,
                   const char **argv, const int argc) {}

void elf_27259_menjaj(const char **argv, const int argc) {
    FILE *file = fopen(argv[1], "r+");
    if (file == NULL) {
        printf("Couldn't open file '%s'\n", argv[1]);
        return;
    }

    Elf32_Ehdr header;
    Elf32_Shdr section;

    fread(&header, sizeof(header), 1, file);

    for (int i = 0; i < header.e_shnum; i++) {
        fseek(file, header.e_shoff + i * header.e_shentsize, SEEK_SET);
        fread(&section, sizeof(Elf32_Shdr), 1, file);

        if (section.sh_type == SHT_SYMTAB) {
            replaceValues(file, header, section, argv, argc);
        }
    }

    fclose(file);
}
