#include <elf.h>
#include <stdio.h>
#include "elf/header.c"

void printUsage() {
    printf("elf_loader [-hlc] [OPTIONS] elf_path\n\n"
           "-h\n  izpis zaglavja zbirke podane v elf_path\n\n"
           "-l\n  izpis vseh funkcij, ki jih najdete v .text sekciji in imajo "
           "velikost večjo od 20 zlogov\n\n"
           "-c [spr1,spr2,spr3,...]\n  spreminjanje vrednosti vseh spremeljivk "
           "programa za +20, ki jih lahko najdete v programu v elf_path\n");
}

int main(const int argc, const char **argv) {
    if (argc < 3) {
        printUsage();
        return 0;
    }

    if (argv[1][0] == '-') {
        if (argv[1][1] == 'h') {
            elf_27259_glava(argv[2]);
            return 0;
        } else if (argv[1][1] == 'l') {
            return 0;
        } else if (argv[1][1] == 'c') {
            return 0;
        }
    }

    printUsage();
}
