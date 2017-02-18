#
# Project:    Homework 1
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the arg and temp_conv
# 	      libraries
#
ARGDIR=./arg
TEMPCONVDIR=./temp_conv

it:
	@echo !!! Creating libraries !!!
	cd $(ARGDIR);\
	$(MAKE) it;\
	cd ../$(TEMPCONVDIR);\
	$(MAKE) it; 

clean:
	@echo !!! Cleaning directories !!!
	cd $(ARGDIR);\
	$(MAKE) clean;\
	cd ../$(TEMPCONVDIR);\
	$(MAKE) clean; 
	
install: 
	@echo !!! Installing the libraries !!!
	cd $(ARGDIR);\
	$(MAKE) install;\
	cd ../$(TEMPCONVDIR);\
	$(MAKE) install; 

depend: 
	@echo !!! Creating dependecies !!!
	cd $(ARGDIR);\
	$(MAKE) depend;\
	cd ../$(TEMPCONVDIR);\
	$(MAKE) depend; 
