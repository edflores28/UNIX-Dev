/*
 *
 *Project: homework 4
 *
 *Progam: monitor_shm - monitor data in shared memory 
 *
 *File Name: monitor_shm.cpp
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "common_struct.h"
#include "shared_mem.h"

using namespace std;

int Counter = 0;

int main (int argc, char *argv[])
{
	// Variables
	int monitor = 30;
	int arraySize = sizeof(shared) * 20;
	shared *shmArry;
	float x = 0.0;
	float y = 0.0;
	int totalValid = 0;
	sigset_t mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTERM);
	sigaddset(&mask, SIGHUP);


	if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
	{
		perror("Error setting signal mask");
	}


	// Check to see if there was an argument
	if (argc == 2)
	{
		monitor = atoi(argv[1]);
	}

	// Obtain the shared region pointer
	void *ptr = connect_shm(SHM_KEY, arraySize);
	shmArry = (shared *) ptr;

	// While loop that contains bulk of the processing
	// and breaks when the counter hits the monitor count.
	while (Counter <= monitor)
	{
		// Find all valid indexes and update the x, y
		// and total valid values.
		for (int i = 0; i < ARRAY_LENGTH; i++) 
		{
			if (shmArry[i].is_valid == 1)
			{
				totalValid++;
				x += shmArry[i].x;
				y += shmArry[i].y;
			}
		}
		
		// Print out the necessary information.
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

	return 0;
}
