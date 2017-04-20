#
# Project:    Homework 4
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates all available libraries
#
EXE=log_mgr thread_mgr shmlib

all it install clean depend:
	-X=`pwd`; \
	for i in $(EXE); do \
		cd $$X/$$i;\
		make $@;\
	done
