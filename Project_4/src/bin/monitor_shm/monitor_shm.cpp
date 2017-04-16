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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "common_struct.h"
#include "shared_mem.h"

using namespace std;

int Counter = 0;

int main (int argc, char *argv[])
{
	int monitor = 30;

	if (argc == 2)
	{
		monitor = atoi(argv[1]);
	}

	cout << "monitor: " << monitor << endl;

	int arraySize = sizeof(shared) * 20;
	
	shared *shmArry;

	void *ptr = connect_shm(1000, arraySize);

	shmArry = (shared *) ptr;


	float x = 0.0;
	float y = 0.0;
	int totalValid = 0;

	while (Counter != monitor)
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

	return 0;
}
