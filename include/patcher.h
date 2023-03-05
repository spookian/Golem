#ifndef GOL_PATCHER_H

#define FILE_LOAD_FAIL 0x80
#define END_RTDLMEM 0x808D120C // magic number that's the end of rtdl's used memory

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

//function for copying the new code over
void golemFileCopy();
//Returns whether or not the given instruction is a branch statement.
uint32_t golemBranchCheck(uint32_t instr);
//Returns a patched branch instruction after being given the original instruction.
uint32_t golemBranchPatch(uint32_t instr);

//dol functions
uint32_t golemGrabStart(void* dol);
uint32_t reverseInt(uint32_t org);

//variables
extern void* baseFile;
extern void* patchFile;

//The current address in the patch dol being read by Golem.
extern uint32_t currentPatchAddr;
//The current address in main.dol being written to by Golem.
extern uint32_t currentPasteAddr;
extern uint32_t baseSize;
extern uint32_t patchSize;
extern uint32_t newSize;

extern uint8_t error_flag;

#endif