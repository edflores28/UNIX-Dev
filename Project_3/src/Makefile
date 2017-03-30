#
# Project:    Homework 2
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates all libraries and executables
#
DIR=lib bin

all it install clean depend:
	-X=`pwd`; \
	for i in $(DIR); do \
		cd $$X/$$i;\
		make $@;\
	done
