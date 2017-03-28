/*
 *Project: homework 3
 *
 *Progam: app2 - Allows the user to created a certain amount
 *               of threads at the specified interal. The program
 *               kills the threads using the SIGALRM signal.
 *
 *File Name: app2.cpp
 *Purpose: TBD
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <iostream>
#include <vector>
#include "log_mgr.h"
#include "thread_mgr.h"
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// Global variable to keep track if the signal
// handler was invoked.
bool AlarmFlag = false;

// The alarm signal handler.
void alrmHandler (int s)
{
	AlarmFlag = true;
	signal (SIGALRM, alrmHandler);
}	

// The fucntion for all created threads.
void *sleepThread (void *)
{
	pause();
}

int main(int argc, char *argv[])
{
	
	if (argc != 3)
	{
		std::cout << "Invalid arguments" << std::endl;
		return -1;
	}
	
	int totalThreads = atoi(argv[1]);
	double totalTime = atof(argv[2]);

	bool validThreads = (totalThreads >= 1) && (totalThreads <= 25);
	bool validTime = (totalTime >= 0.1) && (totalTime <= 10.0);

	if (!validThreads)
	{
		std::cout << "Total threads not in valid range (1-25)" << std::endl;
		return -1;
	}

	if (!validTime)
	{
		std::cout << "The time is not in valid range (0.1-10.0)" << std::endl;
		return -1;
	}
	
	// Variables
	sigset_t newMask, oldMask;
	itimerval timer;
	std::vector<ThreadHandles> ThreadList;
	std::vector<ThreadHandles>::iterator it;

	// Set the masks to be used by sigproc mask.
	sigemptyset(&newMask);
	sigemptyset(&oldMask);

	// Add the signal to newMask and block the signal.
	// This will be inherited by all created threads.
	sigaddset(&newMask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newMask, &oldMask);

	// Configure the timer.
	timer.it_value.tv_sec = 5;
	timer.it_value.tv_usec = 5;
	timer.it_interval = timer.it_value;

	for (int i = 0; i < totalThreads; i++)
	{
		it = ThreadList.end();
		ThreadList.insert(it, th_execute(sleepThread));
		sleep(totalTime);
	}

	// Unblock the alarm signal
	sigprocmask(SIG_SETMASK, &oldMask, NULL);

	// Set the timer.
	if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
	{
		perror ("Error creating timer");
		return -1;
	}

	// Set the alarm signal handler
	signal (SIGALRM, alrmHandler);

	// This loop polls the database with all the created handles.
	// It also checks to see if the alarm flag is set and kills
	// the thread and removes it from the database.
	while(!ThreadList.empty())
	{
		if (AlarmFlag) {
			
			if (th_kill(ThreadList[0]) == THD_ERROR)
				std::cout << "Error cancelling thread with handle: " << ThreadList[0] << std::endl;
			AlarmFlag = false;
			ThreadList.erase(ThreadList.begin());
		}	
	}
	return 0;
}
