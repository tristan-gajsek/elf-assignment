#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void elf_27259_simboli(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Couldn't open file '%s'\n", path);
        return;
    }
    fclose(file);
}
