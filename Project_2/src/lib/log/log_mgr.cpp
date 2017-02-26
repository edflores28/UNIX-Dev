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
	int temp = -1;

	memset(&buffer[0], 0, sizeof(buffer));
	strcpy(buffer, logName.c_str());

	fd = open(buffer, O_APPEND|O_CREAT|O_WRONLY, 0644);

//	temp = fchmod(fd, 666);
//	cout << temp << "chmod" << endl;

	return fd;
}

int log_event(Levels I, const char *fmt, ...)
{
	// Declare all the variables.
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [256];
	va_list args;
	string fullString;
	string formatted;
	ssize_t bytesWritten = -1;

	// Obtain the current time.
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	// Format the time and append it to the string.
	strftime (buffer, 256,"%b %d %T %Z %G:", timeinfo);
	
	fullString.append(string(buffer));
	
	// Append the level to the string
	fullString.append(getText(I));
	
	// Clear the buffer.
	memset(&buffer[0], 0, sizeof(buffer));

	// Obtain the arguments to the function.
	va_start (args, fmt);
	vsprintf (buffer, fmt, args);

	// Append the arguments to the string
	fullString.append(1u,':');
	fullString.append(string(buffer));
	fullString.append(1u, '\n');

	cout << fullString << endl;
	
	memset(&buffer[0], 0, sizeof(buffer));
	strcpy(buffer, logName.c_str());
	
	if (fd == -1)
		openFile(logName);

	memset(&buffer[0], 0, sizeof(buffer));
	strcpy(buffer, fullString.c_str());

	bytesWritten = write(fd, buffer, fullString.length());

	cout << "FD: " << fd << " Bytes: " << bytesWritten << endl;

	return 1;
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

