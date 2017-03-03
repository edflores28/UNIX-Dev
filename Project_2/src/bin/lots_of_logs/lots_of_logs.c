/*
 *Project: homework 2
 *
 *Progam: lots_of_logs - creates and writes big logfile
 *File Name: lots_logs.c
 *Purpose: Generates differents events to the logfile
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */
#include <unistd.h>
#include <stdlib.h>
#include "log_mgr.h"

main()
{
	int i;
	float z = 0.5;

	set_logfile ("BIGlogfile");
	for (i = 0; i < 50; i++)
	{
		log_event (INFO, "[%d]This is test %d for %f", getpid(), i, z);
		log_event (WARNING, "[%d]This is test %d for %f", getpid(), i, z);
		log_event (FATAL, "[%d]This is test %d for %f", getpid(), i, z);
		z = z * 0.98;
	}

	close_logfile();
	exit (0);
}
