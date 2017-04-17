/*
 *Project: homework 4
 *
 *Progam: install_and_monitor - This program installs and monitor
 *                              data into shared memory.
 *
 *File Name: install_and_monitor.cpp
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <iostream>
#include "thread_mgr.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *install (void *)
{
}

void *monitor (void *)

int main(int argc, char *argv[])
{
//	if (argc != 2)
//	{
//		std::cout << "Invalid arguments" << std::endl;
//		return -1;
//	}

	int totalThreads = atoi(argv[1]);
	
	bool validThreads = (totalThreads >= 1) && (totalThreads <= 12);

	if (!validThreads)
	{
		std::cout << "Total threads not in valid range (1-12)" << std::endl;
		return -1;
	}

	ThreadHandles handle = -1;
	int waitAll = -1;

	for (int i = 0; i < totalThreads; i++)
		handle = th_execute(computation);

	waitAll = th_wait_all();

	return 0;
}
