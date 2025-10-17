#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

/* ---- small helpers ------------------------------------------------------- */

static void die(const char *msg)
{
    dprintf(STDERR_FILENO, "Error: %s\n", msg);
    exit(98);
}

static const char *osabi_str(unsigned char osabi)
{
    switch (osabi) {
        case ELFOSABI_SYSV:     return "UNIX - System V";
        case ELFOSABI_HPUX:     return "HP-UX";
        case ELFOSABI_NETBSD:   return "UNIX - NetBSD";
        case ELFOSABI_LINUX:    return "UNIX - Linux";
        case ELFOSABI_SOLARIS:  return "UNIX - Solaris";
        case ELFOSABI_AIX:      return "AIX";
        case ELFOSABI_IRIX:     return "IRIX";
        case ELFOSABI_FREEBSD:  return "UNIX - FreeBSD";
        case ELFOSABI_TRU64:    return "TRU64 UNIX";
        case ELFOSABI_ARM:      return "ARM";
        case ELFOSABI_STANDALONE:return "Standalone App";
        default:                return "<unknown: %u>";
    }
}

static const char *type_str(unsigned int e_type)
{
    switch (e_type) {
        case ET_NONE: return "NONE (None)";
        case ET_REL:  return "REL (Relocatable file)";
        case ET_EXEC: return "EXEC (Executable file)";
        case ET_DYN:  return "DYN (Shared object file)";
        case ET_CORE: return "CORE (Core file)";
        default:      return "<unknown>";
    }
}

/* swap helpers for big endian headers read on little endian machines */
static unsigned short bswap16(unsigned short x)
{
    return (x >> 8) | (x << 8);
}

static unsigned int bswap32(unsigned int x)
{
    return ((x & 0x000000FFU) << 24) |
           ((x & 0x0000FF00U) << 8)  |
           ((x & 0x00FF0000U) >> 8)  |
           ((x & 0xFF000000U) >> 24);
}

static unsigned long long bswap64(unsigned long long x)
{
    return ((x & 0x00000000000000FFULL) << 56) |
           ((x & 0x000000000000FF00ULL) << 40) |
           ((x & 0x0000000000FF0000ULL) << 24) |
           ((x & 0x00000000FF000000ULL) << 8)  |
           ((x & 0x000000FF00000000ULL) >> 8)  |
           ((x & 0x0000FF0000000000ULL) >> 24) |
           ((x & 0x00FF000000000000ULL) >> 40) |
           ((x & 0xFF00000000000000ULL) >> 56);
}

/* ---- main --------------------------------------------------------------- */

int main(int argc, char **argv)
{
    int fd;
    unsigned char ident[EI_NIDENT];
    ssize_t n;

    if (argc != 2)
        die("Usage: elf_header elf_filename");

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        die("Can't open file");

    /* Read just the e_ident first (1st read) */
    n = read(fd, ident, EI_NIDENT);
    if (n != EI_NIDENT)
        die("Can't read ELF header");

    if (ident[EI_MAG0] != ELFMAG0 || ident[EI_MAG1] != ELFMAG1 ||
        ident[EI_MAG2] != ELFMAG2 || ident[EI_MAG3] != ELFMAG3)
        die("Not an ELF file");

    /* Print header title + Magic bytes */
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%02x%c", ident[i], i + 1 == EI_NIDENT ? '\n' : ' ');

    /* Class */
    printf("  Class:                             ");
    if (ident[EI_CLASS] == ELFCLASS32) printf("ELF32\n");
    else if (ident[EI_CLASS] == ELFCLASS64) printf("ELF64\n");
    else printf("Invalid class\n");

    /* Data (endianness) */
    printf("  Data:                              ");
    if (ident[EI_DATA] == ELFDATA2LSB) printf("2's complement, little endian\n");
    else if (ident[EI_DATA] == ELFDATA2MSB) printf("2's complement, big endian\n");
    else printf("Invalid data encoding\n");

    /* Version */
    printf("  Version:                           %d (current)\n",
           ident[EI_VERSION]);

    /* OS/ABI */
    printf("  OS/ABI:                            ");
    {
        const char *s = osabi_str(ident[EI_OSABI]);
        if (s[0] == '<') /* unknown: print numeric */
            printf(s, ident[EI_OSABI]), printf("\n");
        else
            printf("%s\n", s);
    }

    /* ABI Version */
    printf("  ABI Version:                       %d\n", ident[EI_ABIVERSION]);

    /* Now read the rest of the header in one go (2nd read) */
    if (lseek(fd, 0, SEEK_SET) == (off_t)-1)
        die("Can't lseek");
    if (ident[EI_CLASS] == ELFCLASS32) {
        Elf32_Ehdr h32;

        n = read(fd, &h32, sizeof(h32));
        if (n != (ssize_t)sizeof(h32))
            die("Can't read ELF header");

        /* Correct for big endian numbers if needed */
        unsigned short e_type = h32.e_type;
        unsigned int entry   = h32.e_entry;
        if (ident[EI_DATA] == ELFDATA2MSB) {
            e_type = bswap16(e_type);
            entry  = bswap32(entry);
        }

        printf("  Type:                              %s\n", type_str(e_type));
        printf("  Entry point address:               0x%x\n", entry);
    } else if (ident[EI_CLASS] == ELFCLASS64) {
        Elf64_Ehdr h64;

        n = read(fd, &h64, sizeof(h64));
        if (n != (ssize_t)sizeof(h64))
            die("Can't read ELF header");

        unsigned short e_type = h64.e_type;
        unsigned long long entry = h64.e_entry;
        if (ident[EI_DATA] == ELFDATA2MSB) {
            e_type = bswap16(e_type);
            entry  = bswap64(entry);
        }

        printf("  Type:                              %s\n", type_str(e_type));
        printf("  Entry point address:               0x%lx\n", (unsigned long)entry);
    } else {
        /* already printed "Invalid class" above, still exit failure spec */
        die("Unsupported ELF class");
    }

    if (close(fd) == -1)
        die("Can't close file");

    return 0;
}
