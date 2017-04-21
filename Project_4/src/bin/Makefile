#
# Project:    Homework 4
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates all available executables
#
EXE=install_data monitor_data install_and_monitor my_fortune

all it install clean depend:
	-X=`pwd`; \
	for i in $(EXE); do \
		cd $$X/$$i;\
		make $@;\
	done
