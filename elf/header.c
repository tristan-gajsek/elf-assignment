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

void printHeader(Elf32_Ehdr header) {}

void elf_27259_glava(const char *path) {
    Elf32_Ehdr header;
    if (!getHeader(&header, path)) {
        printf("Couldn't read header of file '%s'\n", path);
        return;
    }
    printHeader(header);
}
