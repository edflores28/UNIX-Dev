/*
 *Project: homework 1
 *
 *Library: temp_conv - temperature conversion library
 *File Name: fahr_convert.cpp
 *Purpose: provides a function to convert centigrade to fahrenheit
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include "fahr_convert.h"

const double factor = 9.0/5.0;

double convert_to_fahr (double cent)
{
	return ((cent * factor) + 32.0);
}
