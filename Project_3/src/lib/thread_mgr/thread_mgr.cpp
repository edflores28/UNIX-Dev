/*
 *Project: homework 3
 *
 *Library: thread_mgr - thread manager library
 *File Name: thread_mgr.cpp
 *Purpose: provides utilities that allows thread management
 *
 *Synopsis (Usage and Parameters):
 *	
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include "thread_mgr.h"

#define MAX_THREADS 50

// Enumerations for the thread status.
typedef enum {RUNNING, CANCELED} Status;

// Constant array for the string representation of 
// thread statuses
static const char *enumText[] = {"RUNNING", "CANCELED"};

// Structure that contains the threads information.
struct ThreadInfo
{
	ThreadHandles handle;
	std::string name;
	Status status;
	pthread_t thread;
};

// Vector contraining all the created threads.
std::vector<ThreadInfo> ThreadList;

// Counter that keeps track of all creating threads.
// This is used to create the handle and name for
// the thread.
int CreatedThreads = 0;

bool initial = true;

// This function obtains the text representation of Levels.
const char* getText(Status value)
{
	return enumText[value];
}

void intHandler(int s)
{
	if (!ThreadList.empty())	
		for (int i = 0; i < ThreadList.size(); i++)
			std::cout << "Handle: " << ThreadList[i].handle
				  << " Name: " <<ThreadList[i].name
				  << " Status: " << getText(ThreadList[i].status) 
				  << std::endl;
	else
		std::cout << "There are no threads being managed" << std::endl;

	// Reinstall the signal handler
	signal(SIGINT, intHandler);
}

void quitHandler (int s)
{
	// ***** THIS NEEDS TO BE UPDATED, THIS IS NOT REENTRANT	
	int retVal = th_kill_all();

	// Reinstall the signal handler
	signal(SIGQUIT, quitHandler);
}

int cancel (int idx)
{
	int retVal = -1;

	ThreadList[idx].status = CANCELED;

	if ((retVal = pthread_cancel(ThreadList[idx].thread)) == 0)
	{
		return THD_OK;
	}
	perror("There was an error cancelling the thread");
	return THD_ERROR;
}

int search (ThreadHandles handle)
{
	for (int i = 0; i < ThreadList.size(); i++)
		if (ThreadList[i].handle == handle)
			return i;
	
	return THD_ERROR;
}

ThreadHandles th_execute (Funcptrs ptr)
{
	// Variables.
	pthread_t thread;
	int retVal = -1;

	// Install signal handlers on the initial execute call.
	if (initial)
	{
		signal(SIGINT, intHandler);
		signal(SIGQUIT, quitHandler);
		initial = false;
	}

		
	if (ThreadList.size() < MAX_THREADS)
	{
		if ((retVal = pthread_create (&thread, NULL, ptr, NULL)) == 0)
		{
			// Create the ThreadInfo object.
			ThreadInfo threadInfo;
			std::vector<ThreadInfo>::iterator it = ThreadList.end();

			threadInfo.handle = ++CreatedThreads;
			threadInfo.name = "THREAD" + std::to_string(CreatedThreads);
			threadInfo.thread = thread;
			threadInfo.status = RUNNING;

			ThreadList.insert(it, threadInfo);

			return threadInfo.handle;
		}
		
		perror("There was an error creating the thread");
		return THD_ERROR;
	}

	std::cout << "The maximum amount of threads has been reached." << std::endl;
	return THD_ERROR;
}

int th_wait (ThreadHandles handle)
{
	int idxVal = -1;

	if ((idxVal = search(handle)) == THD_ERROR)
		return THD_ERROR;

	pthread_join(ThreadList[idxVal].thread, NULL);
	ThreadList.erase(ThreadList.begin()+idxVal);

	return THD_OK;
}

int th_wait_all (void)
{
	if (!ThreadList.empty())
	{
		// Join all the threads that are currently in the list.
		for (int i = 0; i < ThreadList.size(); i++)
			pthread_join(ThreadList[i].thread, NULL);


		ThreadList.clear();
		return THD_OK;
	}
	
	return THD_ERROR;
}

int th_kill (ThreadHandles handle) 
{
	int idxVal = -1;

	if ((idxVal = search(handle)) == THD_ERROR)
		return THD_ERROR;

	return cancel(idxVal);
}

int th_kill_all (void)
{
	int retVal = -1;

	if (!ThreadList.empty())
	{
		// Cancel all the threads that are currently in the list.
		for (int i = 0; i < ThreadList.size(); i++)
		{

			retVal = cancel(i);
		}

		return THD_OK;
	}
	
	return THD_ERROR;
}

int th_exit (void)
{
	pthread_t thread = pthread_self();
	
	if (!ThreadList.empty())
	{
		// Cancel all the threads that are currently in the list.
		for (int i = 0; i < ThreadList.size(); i++)
			if (ThreadList[i].thread == thread)
			{
				pthread_exit(NULL);
			}

		return THD_OK;
	}
	
	return THD_ERROR;
}