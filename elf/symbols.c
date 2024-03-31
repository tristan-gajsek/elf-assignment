#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printSymbols(FILE *file, Elf32_Ehdr header, Elf32_Shdr section) {
    Elf32_Sym symbol;
    char symbolName[32];
    symbolName[31] = '\0';

    for (unsigned int i = 0; i < section.sh_size / section.sh_entsize; i++) {
        fseek(file, section.sh_offset + i * section.sh_entsize, SEEK_SET);
        fread(&symbol, sizeof(Elf32_Sym), 1, file);

        if (((symbol.st_info) & 0xF) == STT_FUNC && symbol.st_size > 20) {
            if (symbol.st_name != 0) {
                Elf32_Shdr stringTable;
                fseek(file,
                      header.e_shoff + header.e_shentsize * section.sh_link,
                      SEEK_SET);
                fread(&stringTable, sizeof(Elf32_Shdr), 1, file);

                fseek(file, stringTable.sh_offset + symbol.st_name, SEEK_SET);
                fread(symbolName, sizeof(char), 31, file);
            } else {
                symbolName[0] = '\0';
            }

            printf("[%2d]\t0x%08X\t%d\t%s\n", i, symbol.st_value,
                   symbol.st_size, symbolName);
        }
    }
}

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
