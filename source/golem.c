#include <string.h>
#include <stdio.h>
#include <golem.h>
#include <patcher.h>

/*
* golem -o <full path>		;; golem outputs the result there
* golem -i <full path>		;; golem loads in the compiled elf file
* golem -h					;; golem prints out a list of how-tos
*/

char* filePath = NULL;	//			;; a path to the elf/dol file that will 

int arg_decide(int length, char* str);
int singl_decide(char letter);

//tool for attaching code to a preexisting copy of rtdl, but will be retooled later on for more games
int main(int argc, char** argv)
{
	bool scnd_arg = FALSE;
	void* fileH = fopen("main.dol", "rw");
	void* sFileH;

	if (fileH == NULL)
	{
		printf("ERROR: Return to Dreamland's main.dol not found!\n");
		return 0;
	}

	if (argc == 1)
	{
		printf("ERROR: No path given!\n");
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

	sFileH = fopen(filePath, "rw");
	if (sFileH == NULL)
	{
		return 0;
	}

	fseek(fileH, 0, SEEK_END);
	fseek(sFileH, 0, SEEK_END);

	baseSize = ftell(fileH);
	patchSize = ftell(sFileH);
	printf("%d", baseSize);

	rewind(fileH);
	rewind(sFileH);

	baseFile = malloc(baseSize);
	patchFile = malloc(patchSize);
	
	if ((fread(baseFile, baseSize, 1, fileH) == 0) || (fread(patchFile, patchSize, 1, sFileH) == 0))
	{
		printf("Error: Failure to read files!\n");
		return 0;
	}
	fclose(fileH);
	fclose(sFileH);
	printf("Beginning second phase...\n");
	golemFileCopy();
	void* newFile = fopen("main_new.dol", "w");
	printf("Beginning final phase...\n");
	if (fwrite(baseFile, newSize, 1, newFile) == 0)
	{
		printf("Error: Failure to write files! \n");
		return 0;
	}

	fclose(newFile);
	free(baseFile);
	free(patchFile);
	return 0;
}

int singl_decide(char letter)
{
	switch (letter)
	{
	case 'h':
		printf("This section's not finished yet, NERD!\n");
		break;
	default:
		break;
	}
	return 0;
}

int arg_decide(int length, char* str)
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
			printf("ERROR: More than one path!");
			return 0;
	}
	return 0;
}