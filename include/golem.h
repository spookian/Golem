#ifndef GOLEM_H
#include <string.h> // for malloc
#include <stdio.h> // for printf
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
typedef char bool;

#define GOLEM_PASS 0
#define GOLEM_INC 1
#define GOLEM_ERR 2

#ifdef __linux__
#include <unistd.h>
#include <fcntl.h>

int linux_file_size(void* handle);

//FILE* just annoys me so I wrote a wrapper for windows and linux's file functions
#define GOLEM_FILE_OPEN(A) open(A, O_RDWR) 
#define GOLEM_FILE_SIZE(A) linux_file_size(A)
#define GOLEM_FILE_CLOSE(A) close(A)
#define GOLEM_FILE_LOAD(A, B, C) read(A, C, B) //file handlre, nbytes, pointer to new shit
#define GOLEM_FILE_CREATE(A) open(A, O_RDWR | O_TRUNC | O_CREAT) //a = file path
#define GOLEM_FILE_WRITE(A, B, C) write(A, B, C)//a is handler, b is memory to read from, c is size of chunk

#elif _WIN32
#include <windows.h>

#define GOLEM_FILE_OPEN(A) CreateFileA(A, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) 
#define GOLEM_FILE_SIZE(A) GetFileSize(A, NULL)
#define GOLEM_FILE_CLOSE(A) CloseHandle(A)
#define GOLEM_FILE_LOAD(A, B, C) ReadFile(A, C, B, NULL, NULL) 
#define GOLEM_FILE_CREATE(A) CreateFileA(A, GENERIC_WRITE | GENERIC_READ, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)
#define GOLEM_FILE_WRITE(A, B, C) WriteFile(A, B, C, NULL, NULL)

#endif

#endif