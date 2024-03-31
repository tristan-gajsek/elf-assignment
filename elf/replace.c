#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceValues(FILE *file, Elf32_Ehdr header, Elf32_Shdr section,
                   const char **argv, const int argc) {
    Elf32_Sym symbol;
    char symbolName[32];
    symbolName[31] = '\0';

    printf("IME\tNASLOV\tVREDNOST\tNOVA_VREDNOST\n");
    for (unsigned int i = 0; i < section.sh_size / section.sh_entsize; i++) {
        fseek(file, section.sh_offset + i * section.sh_entsize, SEEK_SET);
        fread(&symbol, sizeof(Elf32_Sym), 1, file);

        if (((symbol.st_info) & 0xF) == STT_OBJECT) {
            if (symbol.st_name == 0) {
                continue;
            }

            Elf32_Shdr stringTable;
            fseek(file, header.e_shoff + header.e_shentsize * section.sh_link,
                  SEEK_SET);
            fread(&stringTable, sizeof(Elf32_Shdr), 1, file);

            fseek(file, stringTable.sh_offset + symbol.st_name, SEEK_SET);
            fread(symbolName, sizeof(char), 31, file);

            for (int i = 2; i < argc; i++) {
                if (strcmp(symbolName, argv[i]) != 0) {
                    continue;
                }

                Elf32_Shdr dataSection;
                fseek(file,
                      header.e_shoff + header.e_shentsize * symbol.st_shndx,
                      SEEK_SET);
                fread(&dataSection, sizeof(Elf32_Shdr), 1, file);

                // Skip if not .bss, .data, or .data1
                if (dataSection.sh_type != SHT_PROGBITS ||
                    dataSection.sh_flags != (SHF_WRITE | SHF_ALLOC)) {
                    continue;
                }

                unsigned int symbolAddress =
                    dataSection.sh_offset + // Section offset in file
                    symbol.st_value -       // Symbol offset in virtual memory
                    dataSection.sh_addr;    // Section offset in virtual memory

                char *symbolValue[sizeof(int)];
                fseek(file, symbolAddress, SEEK_SET);
                fread(symbolValue, sizeof(int), 1, file);
                int newSymbolValue = *(int *)symbolValue + 20;

                printf("%s\t0x%X\t%d\t\t%d\n", symbolName, symbolAddress,
                       *(int *)symbolValue, newSymbolValue);

                fseek(file, symbolAddress, SEEK_SET);
                fwrite(&newSymbolValue, sizeof(int), 1, file);
                break;
            }
        }
    }
}

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
