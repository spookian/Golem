#include <string.h>
#include <stdio.h>
#include <golem.h>
#include <patcher.h>

/*
* golem -o <full path>		;; golem outputs the result there
* golem -i <full path>		;; golem loads in the compiled elf file
* golem -h					;; golem prints out a list of how-tos
*/

#ifdef __linux__
int linux_file_size(void* handle)
{
	struct stat d;
	fstat(handle, &d);
	return d.st_size;
}
#endif

char* filePath = NULL;	//			;; a path to the elf/dol file that will 

int arg_decide(int length, char* str);
int singl_decide(char letter);

//tool for attaching code to a preexisting copy of rtdl, but will be retooled later on for more games
int main(int argc, char** argv)
{
	bool scnd_arg = FALSE;
	void* fileH = GOLEM_FILE_OPEN("main.dol");
	void* sFileH;

	if (fileH == -1)
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

	sFileH = GOLEM_FILE_OPEN(filePath);
	if (sFileH == -1)
	{

		return 0;
	}
	baseSize = GOLEM_FILE_SIZE(fileH);
	patchSize = GOLEM_FILE_SIZE(sFileH);

	baseFile = malloc(baseSize);
	patchFile = malloc(patchSize);
	
	if (!GOLEM_FILE_LOAD(fileH, baseSize, baseFile) || !GOLEM_FILE_LOAD(sFileH, patchSize, patchFile))
	{
		printf("Error: Failure to read files!\n");
		return 0;
	}
	GOLEM_FILE_CLOSE(fileH);
	GOLEM_FILE_CLOSE(sFileH);

	golemFileCopy();
	void* newFile = GOLEM_FILE_CREATE("main_new.dol");
	
	GOLEM_FILE_WRITE(newFile, baseFile, newSize);

	GOLEM_FILE_CLOSE(newFile);
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