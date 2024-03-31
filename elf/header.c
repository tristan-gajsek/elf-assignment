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

const char *getClass(Elf32_Ehdr header) {
    switch (header.e_ident[EI_CLASS]) {
    case ELFCLASSNONE:
        return "Invalid class";
        break;
    case ELFCLASS32:
        return "ELF32";
        break;
    case ELFCLASS64:
        return "ELF64";
        break;
    default:
        return NULL;
        break;
    }
}

const char *getDataEncoding(Elf32_Ehdr header) {
    switch (header.e_ident[EI_DATA]) {
    case ELFDATANONE:
        return "Invalid data encoding";
        break;
    case ELFDATA2LSB:
        return "2's complement, little endian";
        break;
    case ELFDATA2MSB:
        return "2's complement, big endian";
        break;
    default:
        return NULL;
        break;
    }
}

const char *getType(Elf32_Ehdr header) {
    switch (header.e_type) {
    case ET_NONE:
        return "NONE (No file type)";
        break;
    case ET_REL:
        return "REL (Relocatable file)";
        break;
    case ET_EXEC:
        return "EXEC (Executable file)";
        break;
    case ET_DYN:
        return "DYN (Shared object file)";
        break;
    case ET_CORE:
        return "CORE (Core file)";
        break;
    case ET_LOPROC:
        return "LOPROC (Processor-specific)";
        break;
    case ET_HIPROC:
        return "HIPROC (Processor-specific)";
        break;
    default:
        return NULL;
        break;
    }
}

const char *getMachine(Elf32_Ehdr header) {
    switch (header.e_machine) {
    case EM_NONE:
        return "No machine";
        break;
    case EM_M32:
        return "AT&T WE 32100";
        break;
    case EM_SPARC:
        return "SPARC";
        break;
    case EM_386:
        return "Intel 80386";
        break;
    case EM_68K:
        return "Motorola 68000";
        break;
    case EM_88K:
        return "Motorola 88000";
        break;
    case EM_860:
        return "Intel 80860";
        break;
    case EM_MIPS:
        return "MIPS RS3000";
        break;
    default:
        return NULL;
        break;
    }
}

const char *getVersion(Elf32_Ehdr header) {
    switch (header.e_version) {
    case EV_NONE:
        return "0 (Invalid version)";
        break;
    case EV_CURRENT:
        return "1 (Current version)";
        break;
    default:
        return NULL;
        break;
    }
}

const char *getOsAbi(Elf32_Ehdr header) {
    switch (header.e_ident[EI_OSABI]) {
    case ELFOSABI_NONE:
        return "UNIX - System V";
        break;
    case ELFOSABI_HPUX:
        return "UNIX - HP-UX";
        break;
    case ELFOSABI_NETBSD:
        return "UNIX - NetBSD";
        break;
    case ELFOSABI_LINUX:
        return "UNIX - Linux";
        break;
    case ELFOSABI_SOLARIS:
        return "UNIX - Solaris";
        break;
    case ELFOSABI_AIX:
        return "UNIX - AIX";
        break;
    case ELFOSABI_IRIX:
        return "UNIX - IRIX";
        break;
    case ELFOSABI_FREEBSD:
        return "UNIX - FreeBSD";
        break;
    case ELFOSABI_TRU64:
        return "UNIX - TRU64";
        break;
    case ELFOSABI_MODESTO:
        return "Novell - Modesto";
        break;
    case ELFOSABI_OPENBSD:
        return "UNIX - OpenBSD";
        break;
    case ELFOSABI_ARM:
        return "ARM";
        break;
    case ELFOSABI_STANDALONE:
        return "Standalone (embedded) application";
        break;
    default:
        return NULL;
        break;
    }
}

void printHeader(Elf32_Ehdr header) {
    char magic[47];
    getMagic(header, magic);

    printf("ELF Header:\n"
           "  Magic:                             %s\n"
           "  Class:                             %s\n"
           "  Data:                              %s\n"
           "  Version:                           %s\n"
           "  OS/ABI:                            %s\n"
           "  ABI Version:                       %d\n"
           "  Type:                              %s\n"
           "  Machine:                           %s\n"
           "  Version:                           0x%X\n"
           "  Entry point address:               0x%X\n"
           "  Start of program headers:          %d (bytes into file)\n"
           "  Start of section headers:          %d (bytes into file)\n"
           "  Flags:                             0x%X\n"
           "  Size of this header:               %d (bytes)\n"
           "  Size of program headers:           %d (bytes)\n"
           "  Number of program headers:         %d\n"
           "  Size of section headers:           %d (bytes)\n"
           "  Number of section headers:         %d\n"
           "  Section header string table index: %d\n",
           magic, getClass(header), getDataEncoding(header), getVersion(header),
           getOsAbi(header), header.e_ident[EI_ABIVERSION], getType(header),
           getMachine(header), header.e_version, header.e_entry, header.e_phoff,
           header.e_shoff, header.e_flags, header.e_ehsize, header.e_phentsize,
           header.e_phnum, header.e_shentsize, header.e_shnum,
           header.e_shstrndx);
}

void elf_27259_glava(const char *path) {
    Elf32_Ehdr header;
    if (!getHeader(&header, path)) {
        printf("Couldn't read header of file '%s'\n", path);
        return;
    }
    printHeader(header);
}
