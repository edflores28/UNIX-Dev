/*
 *Project: homework 3
 *
 *Progam: app1 - TBD
 *File Name: app1.cpp
 *Purpose: TBD
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <iostream>
#include "getarg.h"
#include "log_mgr.h"
#include "thread_mgr.h"
#include <unistd.h>
#include <pthread.h>

void *computation (void *)
{
	std::cout << " start" << std::endl;
	
	for (int i = 0; i <= 1000000000; i++);

	std::cout << " end" << std::endl;
	int kill = th_exit();
}

int main(int argc, char *argv[])
{
	
	int argSuccess = -1;
	double value = 0.0;
	int totalThreads = -1;

	argSuccess = get_argument(argc, argv, &value);
	totalThreads = (int) value;

	if ((argSuccess == OK) && (totalThreads >= 1) && (totalThreads <= 12))
	{
		
		ThreadHandles handle = -1;
		int waitAll = -1;

		for (int i = 0; i < 12; i++)
			handle = th_execute(computation);

		waitAll = th_wait_all();

		std::cout << "wait: " << waitAll <<  std::endl;

		return 0;
	}
	std::cout << "ERROR" << std::endl;
	return -1;
}

