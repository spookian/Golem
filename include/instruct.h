#ifndef GOL_INS_H
#define GOL_INS_H

#include "types.h"

typedef struct basicins_s
{
	uint32_t type;
	
	struct basicins_s *next;
	struct basicins_s *prev;
} basicins_t;
//basic linked list for instructions, all instructions are children of this struct

typedef struct hookins_s
{
	basicins_t 	node;
	
	char		*symbol_name;
	uint32_t	b_addr;
	uint32_t	r_addr;
	uint32_t	b_off;
	uint32_t	r_off;
	
} hookins_t;

typedef struct defins_s
{
	basicins_t	node;
	
	char 		*name;
	uint32_t	value;
} cusvins_t;

typedef struct inclins_s
{
	basicins_t	node;
	
	char		*path;
} inclins_t;

const char *instr_lookup_tbl[] = 
{
	"\x07Include",
	"\x04Hook",
	"\x06CusVar"
};

typedef enum {
	INST_INCL = 0,
	INST_HOOK,
	INST_CUSVAR
} einst_t;

extern basicins_t* 	current_instruction;
extern basicins_t	starting_instruction;
extern char ini_line_buffer[255];
extern uint32_t current_ini_sect;

void parse_ini_line(FILE *ini_handl);


//list of memory structures that need to be freed
//all of ins_arr, ini files
#endif