/*
 *Project: homework 1
 *
 *Progam: conv_to_fahr - converts a value to fahrenheit
 *File Name: conv_to_fahr.cpp
 *Purpose: obtains a value in centigrade from the user and converts it
 *         to fahrenheit
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <iostream>
#include <iomanip>
#include "fahr_convert.h"

using namespace std;

int main()
{
	double centigrade = 0.0;
	double value = 0.0;

	cout << "Enter number of centigrade degrees: ";

	cin >> centigrade;
	
	value = convert_to_fahr(centigrade);

	cout << setprecision(4) << centigrade << " degree centigrade is ";
	cout << setprecision(4) << value << " Fahrenheit." << endl; 

	return 0;
}
