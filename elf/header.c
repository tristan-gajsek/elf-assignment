#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool getHeader(Elf32_Ehdr *header, const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return false;
    }
    fread(header, sizeof(*header), 1, file);
    fclose(file);
    return true;
}

void getMagic(Elf32_Ehdr header, char *magic) {
    sprintf(magic,
            "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
            "%02X %02X %02X",
            header.e_ident[0], header.e_ident[1], header.e_ident[2],
            header.e_ident[3], header.e_ident[4], header.e_ident[5],
            header.e_ident[6], header.e_ident[7], header.e_ident[8],
            header.e_ident[9], header.e_ident[10], header.e_ident[11],
            header.e_ident[12], header.e_ident[13], header.e_ident[14],
            header.e_ident[15]);
}

void printHeader(Elf32_Ehdr header) {}

void elf_27259_glava(const char *path) {
    Elf32_Ehdr header;
    if (!getHeader(&header, path)) {
        printf("Couldn't read header of file '%s'\n", path);
        return;
    }
    printHeader(header);
}
