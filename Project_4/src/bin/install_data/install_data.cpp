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
#include "common_struct.h"
#include "shared_mem.h"

using namespace std;

int main (int argc, char *argv[])
{
//	if (argc != 2)
//	{
//		std::cout << "Invalid arguments" << std::endl;
//		return -1;
//	}


	string test;

	string index;
	string x;
	string y;
	string time;

	ifstream testing("input_data");

	if (!testing)
	{
		cout << "ERROR OPENING FILE";
		return 0;
	}


	while (getline(testing, test))
	{
		istringstream iss (test);
		iss >> skipws >> index >>  x >> y >> time;
		cout << index << " " <<  x << " " << y << " " << time << endl;
	}

	return 0;
}
