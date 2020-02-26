#ifndef DYLD_ELF64_ELF64_H
#define DYLD_ELF64_ELF64_H

#include <stdint.h>

typedef uintptr_t Elf64_Addr;
typedef uint64_t  Elf64_Off;
typedef uint16_t  Elf64_Half;
typedef uint32_t  Elf64_Word;
typedef int32_t   Elf64_Sword;
typedef uint64_t  Elf64_Xword;
typedef int64_t   Elf64_Sxword;

/**************
 * Elf64_Ehdr *
 **************/

/* e_ident */

#define EI_MAG0       0
#define EI_MAG1       1
#define EI_MAG2       2
#define EI_MAG3       3
#define EI_CLASS      4
#define EI_DATA       5
#define EI_VERSION    6
#define EI_OSABI      7
#define EI_ABIVERSION 8
#define EI_PAD        9
#define EI_NIDENT     16

#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define ELFCLASS64 2

#define ELFDATA2LSB 1

#define ELFOSABI_SYSV       0
#define ELFOSABI_HPUX       1
#define ELFOSABI_STANDALONE 255

/* e_type */

#define ET_NONE   0
#define ET_REL    1
#define ET_EXEC   2
#define ET_DYN    3
#define ET_CORE   4
#define ET_LOOS   0xfe00
#define ET_HIOS   0xfeff
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

/* e_machine */

#define EM_X86_64 62

/* e_version */

#define EV_NONE    0
#define EV_CURRENT 1

/* e_phnum, the following is a maximum value, see SysV ABI AMD64 appendix */

#define PN_XNUM 0xffff

struct Elf64_Ehdr {
	unsigned char e_ident[EI_NIDENT];
	Elf64_Half    e_type;
	Elf64_Half    e_machine;
	Elf64_Word    e_version;
	Elf64_Addr    e_entry;
	Elf64_Off     e_phoff;
	Elf64_Off     e_shoff;
	Elf64_Word    e_flags;
	Elf64_Half    e_ehsize;
	Elf64_Half    e_phentsize;
	Elf64_Half    e_phnum;
	Elf64_Half    e_shentsize;
	Elf64_Half    e_shnum;
	Elf64_Half    e_shstrndx;
};

/**************
 * Elf64_Shdr *
 **************/

struct Elf64_Shdr {
	Elf64_Word  sh_name;
	Elf64_Word  sh_type;
	Elf64_Xword sh_flags;
	Elf64_Addr  sh_addr;
	Elf64_Off   sh_offset;
	Elf64_Xword sh_size;
	Elf64_Word  sh_link;
	Elf64_Word  sh_info;
	Elf64_Xword sh_addralign;
	Elf64_Xword sh_entsize;
};

struct Elf64_Sym {
	Elf64_Word    st_name;
	unsigned char st_info;
	unsigned char st_other;
	Elf64_Half    st_shndx;
	Elf64_Addr    st_value;
	Elf64_Xword   st_size;
};

struct Elf64_Rel {
	Elf64_Addr  r_offset;
	Elf64_Xword r_info;
};

struct Elf64_Rela {
	Elf64_Addr   r_offset;
	Elf64_Xword  r_info;
	Elf64_Sxword r_addend;
};

/**************
 * Elf64_Phdr *
 **************/

/* p_type */

#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6

/* p_type, what's the true usage of those masks? */

#define PT_LOOS    0x60000000
#define PT_HIOS    0x6fffffff
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff

/* p_type, x86_64 specific */
#define PT_GNU_EH_FRAME  0x6474e550
#define PT_SUNW_EH_FRAME 0x6474e550
#define PT_SUNW_UNWIND   0x6464e550

/* p_type, GNU specific? TODO: lookup for documentation */
#define PT_GNU_STACK 0x6474e551
#define PT_GNU_RELRO 0x6474e552

/* nb: lot of other types exist, might need
 external documentation and references
 to implement them */

/* p_flags */

#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x4

/* p_flags, the following differ between elf and elf64,
 elf64 are took, cause we're an elf64 dynamic linker */

#define PF_MASKOS   0x00ff0000
#define PF_MASKPROC 0xff000000

struct Elf64_Phdr {
	Elf64_Word  p_type;
	Elf64_Word  p_flags;
	Elf64_Off   p_offset;
	Elf64_Addr  p_vaddr;
	Elf64_Addr  p_paddr;
	Elf64_Xword p_filesz;
	Elf64_Xword p_memsz;
	Elf64_Xword p_align;
};

struct Elf64_Dyn {
	Elf64_Sxword d_tag;
	union {
		Elf64_Xword d_val;
		Elf64_Addr  d_ptr;
	} d_un;
};

/* DYLD_ELF64_ELF64_H */
#endif
