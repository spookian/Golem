#pragma once
#include <Windows.h>

#define FILE_LOAD_FAIL 0x80


//function for copying the new code over
void golemFileCopy();
//Returns whether or not the given instruction is a branch statement.
UINT32 golemBranchCheck(UINT32 instr);
//Returns a patched branch instruction after being given the original instruction.
UINT32 golemBranchPatch(UINT32 instr);

//dol functions
UINT32 golemGrabStart(void* dol);

UINT32 reverseInt(UINT32 org);

//variables
void* baseFile;
void* patchFile;

//The current address in the patch dol being read by Golem.
UINT32 currentPatchAddr;
//The current address in main.dol being written to by Golem.
UINT32 currentPasteAddr;
UINT32 baseSize;
UINT32 patchSize;
UINT32 newSize;

UCHAR error_flag;