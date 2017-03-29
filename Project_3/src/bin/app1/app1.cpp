/*
 *Project: homework 3
 *
 *Progam: app1 - Allows the user to create a certain amount of
 *               threads. The program will wait until all threads
 *               are completed.
 *
 *File Name: app1.cpp
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <iostream>
#include "log_mgr.h"
#include "thread_mgr.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *computation (void *)
{
	std::cout << " start" << std::endl;
	
	for (int i = 0; i <= 1000000000; i++);

	std::cout << " end" << std::endl;
	int kill = th_exit();
}

int main(int argc, char *argv[])
{
	if (argc !== 2)
	{
		std::cout << "Invalid arguments" << std::endl;
		return -1;
	}

	int totalThreads = atoi(argv[1]);
	
	bool validThreads = (totalThreads >= 1) && (totalThreads <= 12);

	if (!validThreads)
	{
		std::cout << "Total threads not in valid range (1-12)" << std::endl;
		return -1;
	}

	ThreadHandles handle = -1;
	int waitAll = -1;

	for (int i = 0; i < 12; i++)
		handle = th_execute(computation);

	waitAll = th_wait_all();

	std::cout << "wait: " << waitAll <<  std::endl;

	return 0;
}
