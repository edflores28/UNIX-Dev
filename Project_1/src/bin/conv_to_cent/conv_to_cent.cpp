/*
 *Project: homework 1
 *
 *Progam: conv_to_cent - converts a value to centigrade
 *File Name: cent_convert.cpp
 *Purpose: obtains a value in fahrenheiht from the cmd line and converts it
 *         to centigrade
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <iostream>
#include <iomanip>
#include "getarg.h"
#include "cent_convert.h"

using namespace std;

int main (int argc, char* argv[])
{

	int argSuccess = 0;
	double value = 0.0;

	argSuccess = get_argument(argc, argv, &value);

	if (argSuccess == 0)
	{
		cout << setprecision(4) << value  << " degrees Fahrenheiht is "; 
		cout <<	setprecision(4) << convert_to_cent(value);
		cout << " degree centigrade" << endl;
	}

	return 0;
}
