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

//variables
void* baseFile;
void* patchFile;

UINT32 textSect;
//The current address in the patch dol being read by Golem.
UINT32 currentPatchAddr;
//The current address in main.dol being written to by Golem.
UINT32 currentPasteAddr;
UINT32 baseSize;

UCHAR error_flag;