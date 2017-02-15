/*
 *Project: homework 1
 *
 *Library: temp_conv - temperature conversion library
 *File Name: cent_convert.cpp
 *Purpose: provides a function to convert farenheit to centigrade
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include "cent_convert.h"

const double factor = 5.0/9.0;

double convert_to_cent (double fahr)
{
	return ((fahr - 32.0) * factor);
}
