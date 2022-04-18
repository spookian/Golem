#include <stdio.h>
#include <Windows.h>

#include "patcher.h"

UINT32 golemBranchCheck(UINT32 instr)
{
	UCHAR f_byte = (instr >> 24);
	return ((f_byte >= 0x40) & (f_byte <= 0x4B));
}

UINT32 golemBranchPatch(UINT32 instr)
{
	UINT32 branchAddr = currentPatchAddr + ((instr << 6) >> 6);
	branchAddr &= 0xFFFFFFFC;

	UINT32 newOffset = 0, newInstr = 0;
	if (currentPasteAddr > branchAddr)
	{
		newOffset = 0xFFFFFFFF - (currentPasteAddr - branchAddr) + 1;
		newOffset = (newOffset - 0xFC000000); //the reverse branch offset - 0xFC000000 + the base instruction
		//cpaste = 801ffffc
		//branch = 80045048
	}
	else
	{
		newOffset = branchAddr - currentPasteAddr;
	}
	newInstr = newOffset + 0x48000000 + (instr & 0x3);
	return newInstr;
}

UINT32 golemGrabStart(void* dol)
{
	return *(UINT32*)((UCHAR*)dol + 0x1c);
	//lesser men would die from this pointer magic;
	//but i was raised in it
}

void golemFileCopy() //keep in mind that this function assumes you've already loaded the two files into memory
{//and also assumes all of your code is stored in text0
	
	//Setup phase
	UINT32 patchText = reverseInt(*(UINT32*)patchFile);
	UINT32 patchSectSize = reverseInt(*(UINT32*)((UCHAR*)patchFile + 0x90));
	UINT32 *patchPointer = (UINT32*)((UCHAR*)patchFile + patchText);
	newSize = baseSize + patchSectSize;

	baseFile = realloc(baseFile, newSize); //resizes main.dol in memory
	currentPatchAddr = reverseInt(*(UINT32*)((UCHAR*)patchFile + 0xE0));
	currentPasteAddr = 0x808D11C0;

	//Loop phase
	if (baseFile)
	{
		UINT32* basePointer = (UINT32*)((UCHAR*)baseFile + baseSize);
		for (int i = 0; i < (patchSectSize / 4); i++)
		{
			int instr = reverseInt(*patchPointer);
			if (golemBranchCheck(instr))
			{
				*patchPointer = reverseInt(golemBranchPatch(instr));
			}
			*basePointer = *patchPointer;

			patchPointer++;
			basePointer++;
			currentPatchAddr += 4;
			currentPasteAddr += 4;
		}

		//Ending phase
		*(UINT32*)((UCHAR*)baseFile + 0x8) = reverseInt(baseSize);
		*(UINT32*)((UCHAR*)baseFile + 0x98) = reverseInt(patchSectSize);
		*(UINT32*)((UCHAR*)baseFile + 0x50) = reverseInt(0x808D11C0);
	}
	else
	{
		error_flag |= FILE_LOAD_FAIL;
	}
}

UINT32 reverseInt(UINT32 org)
{
	UCHAR x, y, z, w;
	x = (org & 0xFF000000) >> 24;
	y = (org & 0x00FF0000) >> 16;
	z = (org & 0x0000FF00) >> 8;
	w = (org & 0x000000FF);

	UINT32 new = 0;
	new += x + ((UINT32)y << 8) + ((UINT32)z << 16) + ((UINT32)w << 24);
	return new;
}