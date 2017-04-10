/*
 *Project: homework 4
 *
 *Library: shmlib - shared memory library
 *File Name: shmlib.cpp
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
// Definition for the return statuses.
#define ERROR -1
#define OK 0

void *connect_shm(int key, int size);

int detach_shm(void *addr);

int destroy_shm(int key);
