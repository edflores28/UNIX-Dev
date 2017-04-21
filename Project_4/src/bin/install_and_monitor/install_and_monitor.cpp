/*
 *Project: homework 4
 *
 *Progam: install_and_monitor - This program installs data into
 *				shared memory and monitors it.
 *				There is signal handling like
 *				in install_data. (Wasn't able to
 *				get it to override thread_mgr)
 *
 *File Name: install_and_monitor.cpp
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include "common_struct.h"
#include "log_mgr.h"
#include "thread_mgr.h"

#define BUFFER_SIZE 26
#define MAX_SEGMENTS 4096

using namespace std;

// Global Variables
int ShmId = -1;
int *Shared;
int MonitorTime = 30;
int Counter = -1;
string InputFile;
ifstream ReadFile;
bool Hangup = false;
bool Term = false;
ThreadHandles Install;
ThreadHandles Monitor;

// Global Constant
const int Size = ARRAY_LENGTH * sizeof(shared);

// Setter function to set the input file.
void setInput (string input)
{
	InputFile = input;
}

// Getter function to get the input file.
string getInput (void)
{
	return InputFile;
}

// Function that logs an event
void event (Levels level, string text)
{
	cout << text << endl;
	log_event(level, text.c_str());
}

// Function that clears out the shared region.
void clearShared (void)
{
	shared *shmArry = (shared *) Shared;

	for (int i = 0; i <= ARRAY_LENGTH; i++)
	{
		shmArry[i].x = 0.0;
		shmArry[i].y = 0.0;
		shmArry[i].is_valid = 0;
	}
}

void *install (void *)
{
	// Variables for string parsing and conversion from
	// string representations to respective types
	string line;
	string index_str;
	string x_str;
	string y_str;
	string time_str;
	char buffer[BUFFER_SIZE];
	float x = 0.0;
	float y = 0.0;
	int time = 0;
	int index = 0;

	// Variables for the shared region and size
	shared *shmArry;

	ReadFile.open(getInput());
	if (!ReadFile)
	{
		event(FATAL, "Error opening file, terminating");
		th_kill(Install);
	}

	// Connect to the shared region;
	shmArry = (shared *) Shared;

	if (shmArry == NULL)
	{
		event(FATAL, "Shared region pointer is null, terminating");
		th_kill(Install);
	}

	// Clear the shared region
	clearShared();

	while (getline(ReadFile, line))
	{
		// Obtain the current line and obtain the string
		// representations of the values.
		istringstream iss (line);
		iss >> skipws >> index_str >> x_str >> y_str >> time_str;

		// The follwing lines of code converts the string
		// representation of their values into their types.
		strcpy(buffer,x_str.c_str());
		x = atof(buffer);
		
		memset(&buffer[0], 0, sizeof(buffer));
		strcpy(buffer,y_str.c_str());
		y = atof(buffer);

		memset(&buffer[0], 0, sizeof(buffer));
		strcpy(buffer,index_str.c_str());
		index = atoi(buffer);
		
		memset(&buffer[0], 0, sizeof(buffer));
		strcpy(buffer,time_str.c_str());
		time = atoi(buffer);

		// Only do stuff with the converted values
		// if the index within the valid range.
		if ((index >= 0) && (index <= 19))
		{
			if (time >= 0)
			{
				// Sleep for the amount of time then
				// install the data into the shared 
				// region.
				sleep(time);
				shmArry[index].x = x;
				shmArry[index].y = y;
				shmArry[index].is_valid = 1;
			}
			else
			{
				// Otherwise the time is negative and
				// mark the convents of index invalid.
				time = abs(time);
				sleep (time);
				shmArry[index].is_valid = 0;
			}
		}
	}

	// Destroy the shared region before exiting.
	if (shmctl (ShmId, IPC_RMID, 0) == -1)
	{
		perror("shmdestroy error");
		event(WARNING, "Failed to destroy shared region");
	}

	// Exit the thread.
	th_kill(Install);
}

void *monitor (void *)
{
	// Variables
	shared *shmArry;
	float x = 0.0;
	float y = 0.0;
	int totalValid = 0;

	// Connect to the shared region;
	shmArry = (shared *) Shared;

	while (Counter <= MonitorTime)
	{
		for (int i = 0; i < ARRAY_LENGTH; i++) 
		{
			if (shmArry[i].is_valid == 1)
			{
				totalValid++;
				x += shmArry[i].x;
				y += shmArry[i].y;
			}
		}
		
		if (totalValid == 0)
			cout << "At time " << Counter << ": no elements are active" << endl;
		else
			cout << "At time " << Counter << ": " << totalValid << " elements are active: x = "
				<< setprecision(4) << x/totalValid << " and y = " << setprecision(4) << y/totalValid << endl;
		
		sleep(1);
		Counter++;
		x = 0.0;
		y = 0.0;
		totalValid = 0;
	}
	
	// Exit when all processing is done.
	th_kill(Monitor);
}

int main(int argc, char *argv[])
{
	switch (argc)
	{
		case 2:
			setInput(argv[1]);
			break;

		case 3:
			setInput(argv[1]);
			MonitorTime = atoi(argv[2]);
			break;

		default:
			cout << "Invalid arguments" << endl;
			return -1;
	}

	// Variables
	shmid_ds info;
	key_t key;

	// Obtain a key
	key = ftok("/usr/include", 0);

	// Obtain the shared memory Id.
	if ((ShmId = shmget(key, Size, IPC_CREAT | 0666)) == -1)
	{
		perror("shmget error");
		return -1;
	}

	// Obtain information about the shared segement.
	if (shmctl (ShmId, IPC_STAT, &info) == -1)
	{
		perror("shmctl error");
		return -1;
	}

	// Only attach to the shared region if the MAX_SEGMENTS
	// has not been reached.
	if (info.shm_nattch < MAX_SEGMENTS)
	{
		Shared = (int *) shmat (ShmId, NULL, 0);

		if (Shared == (int *) -1)
		{
			perror("shmatt error");
			return 0;
		}
	}

	// Execute the install thread.
	Install = th_execute(install);

	// Execute the monitor thread.
	Monitor = th_execute(monitor);

	// Wait for all threads.
	th_wait_all();

	return 0;
}
