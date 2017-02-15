/*
 *Project: homework 1
 *
 *Library: arg - parse command line library
 *File Name: getarg.cpp
 *Purpose: provides a function to retrieve an argument
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <stdlib.h>
#include "getarg.h"

int get_argument (int argc, char *argv[], double *return_value)
{
	// We only care about the second index of argv since
	// it will contain the value that is needed. The second
	// value will be converted into a float and indicate
	// a success.
	
	if (argc > 1)
	{
		*return_value = atof(argv[1]);
		return 0;
	}
	else
		return -1;

}

