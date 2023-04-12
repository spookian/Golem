#ifndef GOL_ELF_H
#define GOL_ELF_H

#include "types.h"

typedef struct elfhead_s
{
	uint8_t 	e_ident[16];
	uint16_t 	e_type;
	uint16_t	e_machine;
	uint32_t	e_version;
	uint32_t	e_entry;
	uint32_t	e_phoff;	// Offset to program header table
	uint32_t	e_shoff;	// offset to section header table
	uint32_t	e_flags;
	uint16_t	e_ehsize;
	uint16_t	e_phentsize;
	uint16_t	e_phnum;
	uint16_t	e_shentsize;
	uint16_t	e_shnum;
	uint16_t	e_shstrndx;
}
elfhead_t;

typedef struct elfshdr_s
{
	uint32_t	sh_name;
	uint32_t	sh_type;
	uint32_t	sh_flags;
	uint32_t	sh_addr;
	uint32_t	sh_offset;
	uint32_t	sh_size;
	uint32_t	sh_link;
	uint32_t	sh_info;
	uint32_t	sh_addralign;
	uint32_t	sh_entsize;
} elfshdr_t;

typedef struct elfsym_s
{
	uint32_t	st_name;
	uint32_t	st_value;
	uint32_t	st_size;
	uint8_t		st_info;	// information about the 
	uint8_t		st_other;	// symbol visibility not that anyone cares
	uint16_t	st_shndx;	// section index
} elfsym_t;

typedef struct elfrel_s
{
	uint32_t r_offset;
	uint32_t r_info;
} elfrel_t;

typedef struct elfrela_s
{
	uint32_t r_offset;
	uint32_t r_info;
	int r_addend;
} elfrela_t;

typedef struct golelf_s
{
	struct golelf_s *next_node;
	struct golelf_s *prev_node;
	
	elfhead_t 	*start;
	elfshdr_t	*section_table;
	uint32_t	num_sections;

	uint8_t		*string_table;
	uint8_t		*section_strtab;

	elfsym_t	*symbol_table;
	uint32_t 	num_symbols;
} golelf_t; // struct used for interpreting and storing values in the elf

extern uint32_t current_virt_addr;
extern uint32_t total_patch_size;

uint32_t elf_setup_vars(elfhead_t *file, golelf_t *vars);
uint32_t elf_compute_rel(golelf_t *vars);
uint32_t patch_rel(golelf_t *vars, elfrel_t *reltb, uint32_t entries, bool addn);
uint32_t rel_type_ppc32(uint32_t start, uint32_t end, uint32_v_addr, uint32_t type);

#endif