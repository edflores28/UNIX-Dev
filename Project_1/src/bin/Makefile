#
# Project:    Homework 1
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates all programs.
#
CENTDIR=./conv_to_cent
FAHRDIR=./conv_to_fahr

it:
	@echo !!! Creating executables !!!
	cd $(CENTDIR);\
	$(MAKE) it;\
	cd ../$(FAHRDIR);\
	$(MAKE) it; 

clean:
	@echo !!! Cleaning directories !!!
	cd $(CENTDIR);\
	$(MAKE) clean;\
	cd ../$(FAHRDIR);\
	$(MAKE) clean; 
	
install: 
	@echo !!! Installing the executables !!!
	cd $(CENTDIR);\
	$(MAKE) install;\
	cd ../$(FAHRDIR);\
	$(MAKE) install; 

depend: 
	@echo !!! Creating dependecies !!!
	cd $(CENTDIR);\
	$(MAKE) depend;\
	cd ../$(FAHRDIR);\
	$(MAKE) depend; 
