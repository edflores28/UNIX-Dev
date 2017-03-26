/*
 *Project: homework 3
 *
 *Library: thread_mgr - thread manager library
 *File Name: thread_mgr.cpp
 *Purpose: provides utilities that allows thread management
 *
 *Synopsis (Usage and Parameters):
 *	
 *
 *Programmer: Edwin Flores
 *Course: EN.605.414.81
 *
 */

// Definition for the return statuses.
#define THD_ERROR -1
#define THD_OK 0

typedef int ThreadHandles;
typedef void *Funcptrs (void *);

ThreadHandles th_execute (Funcptrs ptr);

int th_wait (ThreadHandles handle);

int th_wait_all (void);

int th_kill (ThreadHandles handle);

int th_kill_all (void);

int th_exit (void);

