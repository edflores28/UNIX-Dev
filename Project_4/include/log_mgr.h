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
#include <string>

// Definition for the return statuses.
#define ERROR -1
#define OK 0

// Global Variables
extern std::string LogName;

typedef enum {INFO, WARNING, FATAL} Levels;

int log_event(Levels I, const char *fmt, ...);

int set_logfile(const char *logfile_name);

void close_logfile(void);
