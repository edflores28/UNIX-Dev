#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "log_mgr.h"

using namespace std;

static const char *enumText[] = {"INFO", "WARNING", "FATAL"};

const char* getText(Levels value)
{
	return enumText[value];
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

	// Obtain the current time.
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	// Format the time and append it to the string.
	strftime (buffer, 256,"%b %d %T %Z %G:", timeinfo);
	
	fullString.append(string(buffer));
	
	// Append the level to the string
	fullString.append(getText(I));
	
	// Clear the buffer.
	buffer[0] = 0;

	// Obtain the arguments to the function.
	va_start (args, fmt);
	vsprintf (buffer, fmt, args);

	// Append the arguments to the string
	fullString.append(1u,':');
	fullString.append(string(buffer));

	cout << fullString << endl;
		
	return 1;
}

int set_logfile(const char *logfile_name)
{
	return 1;
}

void close_logfile(void)
{
}

