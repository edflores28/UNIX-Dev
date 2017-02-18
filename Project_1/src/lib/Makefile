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
	$(MAKE) -C $(ARGDIR) it
	$(MAKE) -C $(TEMPCONVDIR) it

clean:
	$(MAKE) -C $(ARGDIR) clean
	$(MAKE) -C $(TEMPCONVDIR) clean 
	
install: 
	$(MAKE) -C $(ARGDIR) install
	$(MAKE) -C $(TEMPCONVDIR) install

depend: 
	$(MAKE) -C $(ARGDIR) depend
	$(MAKE) -C $(TEMPCONVDIR) depend 
