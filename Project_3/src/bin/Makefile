#
# Project:    Homework 2
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates all available executables
#
EXE=app1 app2

all it install clean depend:
	-X=`pwd`; \
	for i in $(EXE); do \
		cd $$X/$$i;\
		make $@;\
	done
