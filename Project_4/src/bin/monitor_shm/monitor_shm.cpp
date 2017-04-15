/*
 *Project: homework 3
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

//	if (argc != 2)
//	{
//		std::cout << "Invalid arguments" << std::endl;
//		return -1;
//	}


	int arraySize = sizeof(shared) * 20;
	
	shared *shmArry;

	void *ptr = connect_shm(1000, arraySize);

	shmArry = (shared *) ptr;


	while (Counter != monitor)
	{
		for (int i = 0; i < 20; i++) 
		{
			cout << "x: " << shmArry[i].x << "y: " << shmArry[i].y << "valid: " <<shmArry[i].is_valid << endl;
		}
		sleep(1);
		Counter++;
	}
	return 0;
}
