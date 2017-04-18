/*
 *Project: homework 4
 *
 *Progam: my_fortune - This program reads from a pipe and converts
 *                     fortunes to upper case.
 *
 *File Name: my_fortune.cpp
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 56

using namespace std;

int rndTime()
{
	return ((rand() % 8) + 1);
}

int main(int argc, char *argv[])
{
	// Variable declarations
	FILE *read;
	char pipeBuff[BUFFER_SIZE];
	char inputBuff [BUFFER_SIZE];
	int retVal;
	timeval timer;
	time_t start;
	time_t stop;
	fd_set rfds;
	string pipe;
	int waitTime;
	int elapsed;

#ifdef __linux__
	string command = "/home/unix_class/fortune_absaroka/fortune";
#elif __sun
	string command = "/home/unix_class/fortune/fortune";
#else
	string command = NULL;
#endif

	const char *pcmd = command.c_str();

	while (1)
	{

		// Call popen for the fortune program
		if ((read = popen(pcmd, "r")) == NULL)
		{
			perror("popen error");
			return -1;
		}
	
		// Read the buffer to obtain the fortune program's output
		while (fgets(pipeBuff, BUFFER_SIZE, read) != NULL)
		{
			pipe.append(pipeBuff);
			memset(&pipeBuff[0], '\0', sizeof(pipeBuff));
		}
	
		// Convert the data read to uppercase, print and clear
		for (int i = 0; i < pipe.size(); i++)
			pipe.at(i) = toupper(pipe.at(i));

		cout << pipe << endl;
		pipe.clear();

		// Since the fortune program just prints out 1 fortune
		// close the pipe.
		if (pclose(read) == -1)
		{
			perror("pclose error");
			return -1;
		}

		// Set the time variables, elapsed will only be
		// set if select has noticed that stdin is ready
		// to be read and there was no valid parameter
		// in the buffer.
		elapsed = 0;
		waitTime = rndTime();

		// Obtain the start time of select
		time(&start);

restart:
		// Set the rfds
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);

		// Set the timer for select. When select is restarted
		// elapsed will be updated with it's respective time
		// and the timer will be updated.
		timer.tv_sec = waitTime - elapsed;
		timer.tv_usec = 0;

		if ((retVal = select(FD_SETSIZE, &rfds, NULL, NULL, &timer)) == -1)
		{
			perror("select error");
			return -1;
		}

		time(&stop);

		if (FD_ISSET(0, &rfds) == 1)
		{
			// Read stdin. Assuming that the user wont enter
			// more characters than BUFFER_SIZE
			while (fgets(inputBuff, BUFFER_SIZE, stdin) == NULL);

			// If the first character in the buffer is 'q'
			// exit the program
			if (inputBuff[0] == 'q')
				return 0;

			// Obtain the elapsed time in seconds.
			elapsed = (int) difftime(stop, start);
			
			// Only goto restart if there is additional time 
			// to wait.
			if (elapsed < waitTime)
				goto restart;
		}
	}

	return 0;
}
