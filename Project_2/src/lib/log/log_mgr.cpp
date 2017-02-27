#include <fcntl.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "log_mgr.h"
#include <sys/stat.h>

#define BUFFER_SIZE 256

using namespace std;


static const char *enumText[] = {"INFO", "WARNING", "FATAL"};

string logName = "logfile";
int fd = -1;

const char* getText(Levels value)
{
	return enumText[value];
}

int openFile (string log)
{
	char buffer[BUFFER_SIZE];

	strcpy(buffer, logName.c_str());

	fd = open(buffer, O_APPEND|O_CREAT|O_WRONLY, 0644);

	return fd;
}

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
	formatted.append(string(buffer));
	formatted.append(1u, '\n');

	return formatted;
}

int log_event(Levels I, const char *fmt, ...)
{
	ssize_t bytesWritten = -1;
	string formatted;
	char buffer [BUFFER_SIZE];
	va_list args;
	

	if (fd == -1)
	{
		openFile(logName);
		if (fd == -1)
			return -1;
	}

	// Obtain the arguments to the function.
	va_start (args, fmt);
	vsprintf (buffer, fmt, args);

	// Obtain the formatted string.
	formatted = formatLog(I, fmt, buffer);
	
	// Cleanr the buffer.
	memset(&buffer[0], 0, sizeof(buffer));
	strcpy(buffer, formatted.c_str());

	bytesWritten = write(fd, buffer, formatted.length());

	if (bytesWritten == -1)
		return -1;

	return 0;
}

int set_logfile(const char *logfile_name)
{
	logName = string(logfile_name);
	
	if (openFile(logName) == -1)
		return -1;

	return 0;
}

void close_logfile(void)
{
	close(fd);
}

