/*
 *Project: homework 4
 *
 *Progam: install_data - install data into shared memory 
 *
 *File Name: install_data.cpp
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "common_struct.h"
#include "shared_mem.h"

#define BUFFER_SIZE 26

using namespace std;

// Global Variables
void *ShmPtr = NULL;
string InputFile;
ifstream ReadFile;
bool Hangup = false;

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

// Function that clears out the shared region.
void clearShared (void)
{
	shared *shmArry = (shared *) ShmPtr;

	for (int i = 0; i <= ARRAY_LENGTH; i++)
	{
		shmArry[i].x = 0.0;
		shmArry[i].y = 0.0;
		shmArry[i].is_valid = 0;
	}
}

// SIGINT and SIGTERM signal handler
void termination (int sig)
{
	if (detach_shm(ShmPtr) == OK)
		cout << "Detached from shared memory" << endl;

	if  (destroy_shm(SHM_KEY) == OK)
		cout << "Destroyed shared memory" << endl;

	exit(0);
}


void inputProcess (void)
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
	int arraySize = sizeof(shared) * ARRAY_LENGTH;

	ReadFile.open(getInput());

	if (!ReadFile)
	{
		cout << "ERROR OPENING FILE";
		exit(-1);;
	}

	// Connect to the shared region
	ShmPtr = connect_shm(SHM_KEY, arraySize);
	shmArry = (shared *) ShmPtr;

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
}

// SIGHUP signal handler
void hangup (int sig)
{
	// Close the file and force the reading loop
	// not to execute anymore.
	ReadFile.close();
	Hangup = true;
}

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments" << std::endl;
		return -1;
	}

	setInput(argv[1]);

	// Variables for the signal hangler.
	struct sigaction terminate;
	struct sigaction old_action;
	struct sigaction hang;

	// Install the signal handlers
	terminate.sa_handler = termination;
	terminate.sa_flags = SA_RESTART;

	hang.sa_handler = hangup;
	hang.sa_flags = SA_RESTART;

	sigaction(SIGINT, &terminate, &old_action);
	sigaction(SIGTERM, &terminate, &old_action);
	sigaction(SIGHUP, &hang, NULL);

restart:

	inputProcess();

	if (Hangup)
	{
		Hangup = false;
		goto restart;
	}

	// Mark the shared area to be destroyed.
	destroy_shm(SHM_KEY);

	return 0;
}
