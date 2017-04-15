/*
 *Project: homework 4
 *
 *Library: shmlib - shared memory library
 *File Name: shared_mem.cpp
 *Purpose: provides shared memory support
 *
 *Synopsis (Usage and Parameters):
 *	
 *	void *connect_shm (int, int);
 *
 *	int detach_shm (void)
 *
 *	int destroy_shm (int)
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <stdio.h>
#include <sys/shm.h>
#include "shared_mem.h"

#define MAX_SEGMENTS 4096

void *connect_shm(int key, int size)
{
	int shmId = -1;
	int *shared;

	if ((shmId = shmget(key, size, IPC_CREAT | 0666)) == -1)
	{
		perror("shmget error");
		return NULL;
	}

	shared = (int *) shmat (shmId, NULL, 0);

	if (shared == (int *) -1)
	{
		perror("shmatt error");
		return NULL;
	}

	return shared;
}

int detach_shm(void *addr)
{
	return OK;
}

int destroy_shm(int key)
{
	return OK;
}
