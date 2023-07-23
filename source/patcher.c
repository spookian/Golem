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

//keep in mind that this function assumes you've already loaded the two files into memory
//and also assumes all of your code is stored in text0
void golemFileCopy() 
{
	
	//Setup phase
	uint32_t patchText = reverseInt(*(uint32_t*)patchFile);
	//first offset of main.dol is the offset to text0
	uint32_t patchSectSize = reverseInt(*(uint32_t*)((uint8_t*)patchFile + 0x90));

	uint32_t *patchPointer = (uint32_t*)((uint8_t*)patchFile + patchText);
	newSize = baseSize + patchSectSize;

	baseFile = realloc(baseFile, newSize); //resizes main.dol in memory
	currentPatchAddr = reverseInt(*(uint32_t*)((uint8_t*)patchFile + 0x48));
	//im gonna be honest i have no idea how it works
	//it only works cause god's grace decreed that the entry should be the first function
	currentPasteAddr = END_RTDLMEM;

	//Loop phase
	if (baseFile)
	{
		uint32_t* basePointer = (uint32_t*)((uint8_t*)baseFile + baseSize);
		memcpy(basePointer, patchPointer, patchSectSize);
		//Ending phase
		((uint32_t*)baseFile)[2] = reverseInt(baseSize);
		((uint32_t*)baseFile)[0x26] = reverseInt(patchSectSize);
		printf("Copy complete!\n");
		((uint32_t*)baseFile)[0x14] = reverseInt(END_RTDLMEM);
		((uint32_t*)baseFile)[0x38]= ((uint32_t*)patchFile)[0x38];
		// rtdl only uses up to text1, so the new text section takes up text2 in baseFile + 0x50 instead
	}
	else
	{
		error_flag |= FILE_LOAD_FAIL;
	}
	printf("Copy complete!\n");
	return;
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