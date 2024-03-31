#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printSymbols(FILE *file, Elf32_Ehdr header, Elf32_Shdr section) {}

void elf_27259_simboli(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Couldn't open file '%s'\n", path);
        return;
    }

    Elf32_Ehdr header;
    Elf32_Shdr section;

    fread(&header, sizeof(header), 1, file);

    printf("[Nr]\tValue\t\tSize\tName\n");
    for (int i = 0; i < header.e_shnum; i++) {
        fseek(file, header.e_shoff + i * header.e_shentsize, SEEK_SET);
        fread(&section, sizeof(Elf32_Shdr), 1, file);

        if (section.sh_type == SHT_SYMTAB) {
            printSymbols(file, header, section);
        }
    }

    fclose(file);
}
