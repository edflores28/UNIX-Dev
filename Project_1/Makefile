#
# Project:    Homework 1
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the arg and temp_conv
# 	      libraries
#
LIB=src/lib
BIN=src/bin

LIBRARIES=/lib/libtempconv.a /lib/libarg.a

$(LIBRARIES):
	cd $(LIB);\
	$(MAKE) it;\
	$(MAKE) install;
	

.PHONY: it 
it: $(LIBRARIES)
	cd $(BIN);\
	$(MAKE) it;\

.PHONY: clean
clean:
	cd $(LIB);\
	$(MAKE) clean;\
	cd ../../$(BIN);\
	$(MAKE) clean; 

.PHONY: install 
install: it
	cd $(LIB);\
	$(MAKE) install;\
	cd ../../$(BIN);\
	$(MAKE) install; 

.PHONY: depend 
depend: 
	cd $(LIB);\
	$(MAKE) depend;\
	cd ../../$(BIN);\
	$(MAKE) depend; 
