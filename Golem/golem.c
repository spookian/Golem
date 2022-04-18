#include <stdio.h>
#include <Windows.h>

#include "golem.h"
#include "patcher.h"

/*
* golem -o <full path>		;; golem outputs the result there
* golem -i <full path>		;; golem loads in the compiled elf file
* golem -h					;; golem prints out a list of how-tos
*/

HANDLE output;
char* filePath = NULL;	//			;; a path to the elf/dol file that will 
char* optFilePath = NULL;

errno_t arg_decide(int length, char* str);
errno_t singl_decide(char letter);

//tool for attaching code to a preexisting copy of rtdl, but will be retooled later on for more games
int main(int argc, char** argv)
{
	BOOL scnd_arg = FALSE;
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE fileH = CreateFileA("main.dol", GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileH == INVALID_HANDLE_VALUE)
	{
		WriteConsoleA(output, "ERROR: Return to Dreamland's main.dol not found!\n", 50, NULL, NULL);
		return 0;
	}

	if (argc == 1)
	{
		WriteConsoleA(output, "ERROR: No path given!\n", 23, NULL, NULL);
		return 0;
	}

	for (int i = 1; i < argc; i++)
	{
		switch (arg_decide(strlen(argv[i]), argv[i]))
		{
			case GOLEM_PASS:
			break;
			case GOLEM_INC:
			i++;
			case GOLEM_ERR:
			return 0;
		}
	}
	WriteConsoleA(output, filePath, strlen(filePath), NULL, NULL);
	WriteConsoleA(output, "\n", 1, NULL, NULL);
	
	//testing something
	currentPatchAddr = 0x80000000;
	currentPasteAddr = 0x801FC754;

	char buffer[10];
	_itoa_s(golemBranchPatch(0x48017964), buffer, 10, 16); //offset is 17964
	WriteConsoleA(output, buffer, 8, NULL, NULL);

	//load files into memory
	//manually copy each byte in text section
	//


	return 0;
}

errno_t singl_decide(char letter)
{
	switch (letter)
	{
	case 'h':
		WriteConsoleA(output, "This section's not finished yet, NERD!\n", 40, NULL, NULL);
		break;
	default:
		break;
	}
	return 0;
}

errno_t arg_decide(int length, char* str)
{
	if (length == 2)
	{
		return singl_decide(str[length - 1]);
	}
	else
	{
		if (!filePath)
			filePath = str;
		else
			WriteConsoleA(output, "ERROR: More than one path!", 27, NULL, NULL);
			return 0;
	}
	return 0;
}