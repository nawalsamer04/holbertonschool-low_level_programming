#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

/* ---- helpers ---------------------------------------------------------- */

static void fatal(const char *msg, const char *arg, int code)
{
	dprintf(STDERR_FILENO, "Error: %s %s\n", msg, arg ? arg : "");
	exit(code);
}

static void print_magic(const unsigned char *e_ident)
{
	int i;

	printf("ELF Header:\n");
	printf("  Magic:  ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", e_ident[i]);
		if (i != EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

static const char *class_str(unsigned char c)
{
	if (c == ELFCLASS32) return "ELF32";
	if (c == ELFCLASS64) return "ELF64";
	return "none";
}

static const char *data_str(unsigned char d)
{
	if (d == ELFDATA2LSB) return "2's complement, little endian";
	if (d == ELFDATA2MSB) return "2's complement, big endian";
	return "none";
}

static const char *osabi_str(unsigned char os)
{
	switch (os)
	{
	case ELFOSABI_SYSV:   return "UNIX - System V";
	case ELFOSABI_HPUX:   return "HP-UX";
	case ELFOSABI_NETBSD: return "UNIX - NetBSD";
	case ELFOSABI_LINUX:  return "UNIX - Linux";
	case ELFOSABI_SOLARIS:return "UNIX - Solaris";
	case ELFOSABI_IRIX:   return "IRIX";
	case ELFOSABI_FREEBSD:return "UNIX - FreeBSD";
	case ELFOSABI_TRU64:  return "TRU64 UNIX";
	case ELFOSABI_ARM:    return "ARM";
	case ELFOSABI_STANDALONE: return "Standalone App";
	default:              return "<unknown: %u>";
	}
}

static unsigned short be16(unsigned short x)
{
	return (x >> 8) | (x << 8);
}

static unsigned int be32(unsigned int x)
{
	return ((x & 0x000000FF) << 24) |
	       ((x & 0x0000FF00) << 8)  |
	       ((x & 0x00FF0000) >> 8)  |
	       ((x & 0xFF000000) >> 24);
}

static unsigned long be64(unsigned long x)
{
	return ((x & 0x00000000000000FFUL) << 56) |
	       ((x & 0x000000000000FF00UL) << 40) |
	       ((x & 0x0000000000FF0000UL) << 24) |
	       ((x & 0x00000000FF000000UL) << 8)  |
	       ((x & 0x000000FF00000000UL) >> 8)  |
	       ((x & 0x0000FF0000000000UL) >> 24) |
	       ((x & 0x00FF000000000000UL) >> 40) |
	       ((x & 0xFF00000000000000UL) >> 56);
}

static const char *type_str(unsigned short t)
{
	switch (t)
	{
	case ET_NONE: return "NONE (None)";
	case ET_REL:  return "REL (Relocatable file)";
	case ET_EXEC: return "EXEC (Executable file)";
	case ET_DYN:  return "DYN (Shared object file)";
	case ET_CORE: return "CORE (Core file)";
	default:      return "<unknown>";
	}
}

/* ---- main ------------------------------------------------------------- */

int main(int ac, char **av)
{
	int fd;
	ssize_t n;
	unsigned char ident[EI_NIDENT];

	if (ac != 2)
		fatal("Usage: elf_header elf_filename", "", 98);

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		fatal("Can't read file", av[1], 98);

	/* We’re allowed to read at most twice; 1st read: EI_NIDENT, then rest */
	n = read(fd, ident, EI_NIDENT);
	if (n != EI_NIDENT)
	{
		close(fd);
		fatal("Not an ELF file - read error:", av[1], 98);
	}
	if (ident[EI_MAG0] != ELFMAG0 || ident[EI_MAG1] != ELFMAG1 ||
	    ident[EI_MAG2] != ELFMAG2 || ident[EI_MAG3] != ELFMAG3)
	{
		close(fd);
		fatal("Not an ELF file:", av[1], 98);
	}

	print_magic(ident);
	printf("  Class:                             %s\n", class_str(ident[EI_CLASS]));
	printf("  Data:                              %s\n", data_str(ident[EI_DATA]));
	printf("  Version:                           %d (current)\n", ident[EI_VERSION]);

	/* OS/ABI */
	if (osabi_str(ident[EI_OSABI]) == (const char *)"<unknown: %u>")
		printf("  OS/ABI:                            <unknown: %u>\n", ident[EI_OSABI]);
	else
		printf("  OS/ABI:                            %s\n", osabi_str(ident[EI_OSABI]));

	printf("  ABI Version:                       %d\n", ident[EI_ABIVERSION]);

	/* Second (and last) read: the rest of the ELF header, class-dependent */
	if (ident[EI_CLASS] == ELFCLASS32)
	{
		Elf32_Ehdr h32;
		/* we already consumed EI_NIDENT bytes; seek back to start and read full header */
		if (lseek(fd, 0, SEEK_SET) == (off_t)-1)
		{
			close(fd);
			fatal("Can't lseek file", av[1], 98);
		}
		if (read(fd, &h32, sizeof(h32)) != (ssize_t)sizeof(h32))
		{
			close(fd);
			fatal("Error reading header from", av[1], 98);
		}

		unsigned short e_type = h32.e_type;
		unsigned long e_entry = h32.e_entry;

		if (ident[EI_DATA] == ELFDATA2MSB)
		{
			e_type = be16(e_type);
			e_entry = be32((unsigned int)e_entry);
		}

		printf("  Type:                              %s\n", type_str(e_type));
		printf("  Entry point address:               0x%x\n", (unsigned int)e_entry);
	}
	else if (ident[EI_CLASS] == ELFCLASS64)
	{
		Elf64_Ehdr h64;
		if (lseek(fd, 0, SEEK_SET) == (off_t)-1)
		{
			close(fd);
			fatal("Can't lseek file", av[1], 98);
		}
		if (read(fd, &h64, sizeof(h64)) != (ssize_t)sizeof(h64))
		{
			close(fd);
			fatal("Error reading header from", av[1], 98);
		}

		unsigned short e_type = h64.e_type;
		unsigned long e_entry = h64.e_entry;

		if (ident[EI_DATA] == ELFDATA2MSB)
		{
			e_type = be16(e_type);
			e_entry = be64(e_entry);
		}

		printf("  Type:                              %s\n", type_str(e_type));
		printf("  Entry point address:               0x%lx\n", e_entry);
	}
	else
	{
		close(fd);
		fatal("Unknown ELF class in", av[1], 98);
	}

	if (close(fd) == -1)
		fatal("Can't close fd", "", 98);

	return (0);
}

