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

#include "shared_mem.h"

void *connect_shm(int key, int size)
{
	return nullptr;
}

int detach_shm(void *addr)
{
	return OK;
}

int destroy_shm(int key)
{
	return OK;
}
