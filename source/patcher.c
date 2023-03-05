#include <patcher.h>
#include <stdlib.h>

void* baseFile;
void* patchFile;

uint32_t currentPatchAddr;
uint32_t currentPasteAddr;
uint32_t baseSize;
uint32_t patchSize;
uint32_t newSize;

uint8_t error_flag;

uint32_t golemBranchCheck(uint32_t instr)
{
	uint8_t f_byte = (instr >> 24);
	return ((f_byte >= 0x40) & (f_byte <= 0x4B));
}

uint32_t golemBranchPatch(uint32_t instr)
{
	uint32_t branchAddr = currentPatchAddr + ((instr << 6) >> 6);
	branchAddr &= 0xFFFFFFFC;

	uint32_t newOffset = 0, newInstr = 0;
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

uint32_t golemGrabStart(void* dol)
{
	return *(uint32_t*)((uint8_t*)dol + 0x1c);
	//lesser men would die from this pointer magic;
	//but i was raised in it
}

//keep in mind that this function assumes you've already loaded the two files into memory
//and also assumes all of your code is stored in text0
void golemFileCopy() 
{
	
	//Setup phase
	uint32_t patchText = reverseInt(*(uint32_t*)patchFile);
	uint32_t patchSectSize = reverseInt(*(uint32_t*)((uint8_t*)patchFile + 0x90));
	uint32_t *patchPointer = (uint32_t*)((uint8_t*)patchFile + patchText);
	newSize = baseSize + patchSectSize;

	baseFile = realloc(baseFile, newSize); //resizes main.dol in memory
	currentPatchAddr = reverseInt(*(uint32_t*)((uint8_t*)patchFile + 0xE0));
	currentPasteAddr = 0x808D11C0;

	//Loop phase
	if (baseFile)
	{
		uint32_t* basePointer = (uint32_t*)((uint8_t*)baseFile + baseSize);
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
		*(uint32_t*)((uint8_t*)baseFile + 0x8) = reverseInt(baseSize);
		*(uint32_t*)((uint8_t*)baseFile + 0x98) = reverseInt(patchSectSize);
		*(uint32_t*)((uint8_t*)baseFile + 0x50) = reverseInt(0x808D11C0);
	}
	else
	{
		error_flag |= FILE_LOAD_FAIL;
	}
}

uint32_t reverseInt(uint32_t org)
{
	uint8_t x, y, z, w;
	x = (org & 0xFF000000) >> 24;
	y = (org & 0x00FF0000) >> 16;
	z = (org & 0x0000FF00) >> 8;
	w = (org & 0x000000FF);

	uint32_t new = 0;
	new += x + ((uint32_t)y << 8) + ((uint32_t)z << 16) + ((uint32_t)w << 24);
	return new;
}