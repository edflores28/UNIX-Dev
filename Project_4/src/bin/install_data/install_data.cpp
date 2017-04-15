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


	// Variables for string parsing
	string line;
	string index_str;
	string x_str;
	string y_str;
	string time_str;

	char buffer[26];

	// Variables for the shared data region
	float x = 0.0;
	float y = 0.0;
	int time = 0;
	int index = 0;

	ifstream readFile("input_data");

	if (!readFile)
	{
		cout << "ERROR OPENING FILE";
		return 0;
	}


	while (getline(readFile, line))
	{
		istringstream iss (line);
		iss >> skipws >> index_str >> x_str >> y_str >> time_str;

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

		cout << index << " " << x << " " << y << " " << time << endl;
	}

	return 0;
}
