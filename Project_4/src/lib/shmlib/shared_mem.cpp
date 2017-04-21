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
#include <iostream>
#include <stdio.h>
#include <sys/shm.h>
#include "shared_mem.h"

#define MAX_SEGMENTS 4096

void *connect_shm(int key, int size)
{
	int shmId = -1;
	int *shared;
	shmid_ds info;

	// Obtain the shared memory Id.
	if ((shmId = shmget(key, size, IPC_CREAT | 0666)) == -1)
	{
		perror("shmget error");
		return NULL;
	}

	// Obtain information about the shared segement.
	if (shmctl (shmId, IPC_STAT, &info) == -1)
	{
		perror("shmctl error");
		return NULL;
	}

	// Only attach to the shared region if the MAX_SEGMENTS
	// has not been reached.
	if (info.shm_nattch < MAX_SEGMENTS)
	{
		shared = (int *) shmat (shmId, NULL, 0);

		if (shared == (int *) -1)
		{
			perror("shmatt error");
			return NULL;
		}

		return shared;
	}

	std::cout << "Maximum segements has been reached, unabled to attach" << std::endl;
	return NULL;
}

int detach_shm(void *addr)
{
	if (shmdt (addr) == -1)
	{
		perror("shmdt error");
		return ERROR;
	}

	return OK;
}

int destroy_shm(int key)
{
	// Obtain the shared memory Id
	int shmId = -1;
	shmid_ds info;

	if ((shmId = shmget(key, 0,0)) == -1)
	{
		perror("shmget error in dest function");
		return ERROR;
	}

	// Obtain information about the shared segement.
	if (shmctl (shmId, IPC_STAT, &info) == -1)
	{
		perror("shmctl error in dest function");
		return ERROR;
	}
	
	// Mark the shared region for destruction.
	if (shmctl (shmId, IPC_RMID, 0) == -1)
	{
		perror("shmdestroy error");
		return ERROR;
	}

	return OK;
}
