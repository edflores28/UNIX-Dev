/*
 *Project: homework 3
 *
 *Library: thread_mgr - thread manager library
 *File Name: thread_mgr.cpp
 *Purpose: provides utilities that allows thread management
 *
 *Synopsis (Usage and Parameters):
 *	
 *	ThreadHandles th_execute (Funcptrs);
 *
 *	int th_wait (ThreadHandles);
 *
 *	int th_wait_all ();
 *
 *	int th_kill (ThreadHandles);
 *
 *	int th_kill_all ();
 *
 *	int th_exit ();
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
#include "log_mgr.h"
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

// Flag to keep track initial starup
bool initial = true;

// Flag that keeps track if the SIGQUIT handle
// was called.
bool sigQuit = false;

// This function obtains the text representation of Levels.
const char* getText(Status value)
{
	return enumText[value];
}

// The SIGINT signal handler. This prints out information
// of all threads in the database.
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

// The SIGQUIT signal handker. This cancels all the threads.
void quitHandler (int s)
{
	sigQuit = true;

	// Reinstall the signal handler
	signal(SIGQUIT, quitHandler);
}

// Function for the sleeping thread.
void *signalThread (void *)
{
	while(1)
	{
		if (sigQuit)
		{
			int retVal = th_kill_all();
			sigQuit = false;
		}
	}
}

// This cancels the thread with the specified handler
int cancel (int idx)
{
	int retVal = -1;

	// If the thread was already cancelled return.
	if (ThreadList[idx].status == CANCELED)
			return THD_OK;

	if ((retVal = pthread_cancel(ThreadList[idx].thread)) == 0)
	{	
		ThreadList[idx].status = CANCELED;
		log_event(INFO, "Thread with %d handle canceled", ThreadList[idx].handle);
		std::cout << "Thread with " << ThreadList[idx].handle << " handle canceled" << std::endl;
		return THD_OK;
	}	

	log_event(FATAL, "Thread with %d handle could not be canceled", ThreadList[idx].handle);
	perror("There was an error cancelling the thread");

	return THD_ERROR;
}

// This searches for the thread with the given handle.
int search (ThreadHandles handle)
{
	for (int i = 0; i < ThreadList.size(); i++)
		if (ThreadList[i].handle == handle)
			return i;
	
	return THD_ERROR;
}


// Externally available functions are below.

ThreadHandles th_execute (Funcptrs ptr)
{
	// Variables.
	pthread_t thread;
	int retVal = -1;

	// Do processing on the initial execute call.
	if (initial)
	{
		// Install the signal handlers.
		signal(SIGINT, intHandler);
		signal(SIGQUIT, quitHandler);

		// Create the signal handling thread.
		retVal = pthread_create(&thread, NULL, signalThread, NULL);

		// Do processing to remove SIGINT and SIGQUIT
		// for the threads to be managed.
		sigset_t newMask;
		sigemptyset(&newMask);

		sigaddset(&newMask, SIGINT);
		sigaddset(&newMask, SIGQUIT);

		sigprocmask(SIG_BLOCK, &newMask, NULL);

		initial = false;
		retVal = -1;
		thread =  0;
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

			log_event(INFO, "Thread with %d handle was created", threadInfo.handle);
			std::cout << "Thread with " << threadInfo.handle << " was created" << std::endl;
			return threadInfo.handle;
		}
		
		log_event(FATAL, "Thread was unabled to be created");
		perror("There was an error creating the thread");
		return THD_ERROR;
	}
	
	log_event(FATAL, "Maximum thread limit reached. Unable to create the thread");
	std::cout << "The maximum amount of threads has been reached." << std::endl;
	return THD_ERROR;
}

int th_wait (ThreadHandles handle)
{
	int idxVal = -1;
	int retVal = -1;

	if ((idxVal = search(handle)) == THD_ERROR)
		return THD_ERROR;

	log_event(INFO, "Waiting for thread with hande %d", handle);
	std::cout << "Waiting for the thread with handle: " << handle << std::endl;

	retVal = pthread_join(ThreadList[idxVal].thread, NULL);

	if (retVal == 0)
	{
		log_event(INFO, "Thread with handle %d terminated", handle);
		std::cout << "Thread with handle was terminated: " << handle << std::endl;

		ThreadList.erase(ThreadList.begin()+idxVal);
		return THD_OK;
	}

	perror ("Error joining thread");
	log_event(FATAL, "There was an error joining thread with handle %d", handle);

	return THD_ERROR;
}

int th_wait_all (void)
{
	if (!ThreadList.empty())
	{;
		int retVal = -1;

		log_event(INFO, "Waiting for all threads");
		std::cout << "Waiting for all threads " << std::endl;

		// Join all the threads that are currently in the list.
		for (int i = 0; i < ThreadList.size(); i++)
		{
		
			retVal = pthread_join(ThreadList[i].thread, NULL);
			
			if (retVal == 0)
			{	
				log_event(INFO, "Thread with handle %d terminated", ThreadList[i].handle);
				std::cout << "Thread with handle was terminated: " << ThreadList[i].handle << std::endl;
			}
			else
			{
				perror ("Error joining thread");
				log_event(FATAL, "There was an error joining thread with handle %d", ThreadList[i].handle);
			}
		}

		ThreadList.clear();
		return THD_OK;
	}
	
	return THD_ERROR;
}

int th_kill (ThreadHandles handle) 
{
	int idxVal = -1;

	if ((idxVal = search(handle)) == THD_ERROR)
	{
		log_event(FATAL, "Thread cannot be canceled, the handle was not found");
		return THD_ERROR;
	}

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

	log_event(FATAL, "Thread cannot be canceled database is empty.");
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
