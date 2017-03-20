/*
 *Project: homework 2
 *
 *Library: log_mgr - log manager library
 *File Name: log_mgr.cpp
 *Purpose: provides utilities that allow setting logfile names, closing
 *         logfiles, and writing to logfiles.
 *
 *Synopsis (Usage and Parameters):
 *	
 *	logEvents (Levels, const char, ...)
 *
 * 	setLogfile (const char)
 *
 * 	closeLogfile ()
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <algorithm>
#include <iostream>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "log_mgr.h"

// Constant value for the buffer size.
#define BUFFER_SIZE 256

using namespace std;

// Constant array for the string representation of 
// Levels.
static const char *enumText[] = {"INFO", "WARNING", "FATAL"};

// Global variables.
string LogName = "logfile";
int Fd = -1;

// This function obtains the text representation of Levels.
const char* getText(Levels value)
{
	return enumText[value];
}

// This function takes a converts a string to char array. When
// the string is larger than BUFFER_SIZE the string will be 
// truncated.
void copyString (char *arry, string value)
{
	size_t totalSize = value.length();

	if (totalSize > BUFFER_SIZE)
		totalSize = BUFFER_SIZE;

	strncpy(arry, value.c_str(), totalSize);
}

// This function opens a file.
int openFile (string log)
{
	char buffer[BUFFER_SIZE];
	int tempFd = -1;

	// Clear the buffer.
	memset(&buffer[0], 0, sizeof(buffer));
	
	// Copy the LogName value into the buffer
	copyString(buffer, log);

	tempFd = open(buffer, O_APPEND|O_CREAT|O_WRONLY, 0644);

	if (tempFd == -1)
	{
		perror("There was an error");
		return -1;
	}

	return tempFd;
}

// This function obtains the raw log entry and converts it
// to the formatted log entry.
string formatLog (Levels I, const char *fmt, char *args)
{
	// Declare all the variables.
	time_t rawtime;
	struct tm * timeinfo;
	string formatted;
	char buffer[BUFFER_SIZE];

	// Obtain the current time.
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	// Format the time and append it to the string.
	strftime (buffer, BUFFER_SIZE,"%b %d %T %Z %G:", timeinfo);
	
	formatted.append(string(buffer));
	
	// Append the level to the string
	formatted.append(getText(I));
	
	// Clear the buffer.
	memset(&buffer[0], 0, sizeof(buffer));

	// Append the arguments and formatting to the string.
	formatted.append(1u,':');
	formatted.append(string(args));
	formatted.append(1u, '\n');

	return formatted;
}

int log_event(Levels I, const char *fmt, ...)
{
	ssize_t bytesWritten = -1;
	string formatted;
	char buffer [BUFFER_SIZE];
	va_list args;
	int tempFd = -1;

	// If there is an invalid file descriptor attemp to open
	// the file with the current logfile name.
	// If the logfile cannot be opened return otherwise
	// set the file descriptor.
	if (Fd == -1)
	{
		tempFd = openFile(LogName);
		if (tempFd == -1)
			return -1;

		Fd = tempFd;
	}

	// Obtain the arguments to the function.
	va_start (args, fmt);
	vsprintf (buffer, fmt, args);

	// Obtain the formatted string.
	formatted = formatLog(I, fmt, buffer);
	
	// Clear the buffer.
	memset(&buffer[0], 0, sizeof(buffer));
	copyString(buffer, formatted);

	// Write to the file.
	bytesWritten = write(Fd, buffer, formatted.length());

	// Return an error if there was an error writing to the
	// logfile.
	if (bytesWritten == -1)
		return -1;

	return 0;
}

int set_logfile(const char *logfile_name)
{
	string tempLog = string(logfile_name);
	int tempFd = -1;

	// Attempt to open the logfile
	tempFd = openFile(tempLog);
	
	// Return an error if there was an error
	// opening the logfile.
	if (tempFd == -1)
		return -1;

	// Set the log name, file descriptor and
	// close the previous file.
	close(Fd);
	LogName = tempLog;
	Fd = tempFd;

	return 0;
}

void close_logfile(void)
{
	// Close the log file and reset the descriptor
	close(Fd);
	Fd = -1;
}

