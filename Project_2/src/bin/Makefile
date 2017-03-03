#
# Project:    Homework 2
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates all available executables
#
EXE=test_log test_log2 lots_of_logs

all it install clean depend:
	-X=`pwd`; \
	for i in $(EXE); do \
		cd $$X/$$i;\
		make $@;\
	done
