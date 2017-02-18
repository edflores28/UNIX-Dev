#
# Project:    Homework 1
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the temp_conv library
#
INCLUDE=../../../include
LIBDIR=../../../lib
SRCS=cent_convert.cpp fahr_convert.cpp
OBJ=$(SRCS:.cpp=.o)
LIB=libtemp_conv.a
LIBDEPEND=depend.mk

CFLAGS=-c -g -Wall -I$(INCLUDE)

all: it

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

%.o: %.cpp 
	g++ $(CFLAGS) $< 

.PHONY: it
it: $(LIB)
	@echo !!! Creating temp_conv library !!!

.PHONY: install
install: it
	@echo !!! Installing the temp_conv library !!!
	install -c -m 666 $(LIB) $(LIBDIR)

.PHONY: clean
clean:
	@echo !!! Cleaning directories !!!
	rm -f *.o *.a *.mk
	rm -f $(LIBDIR)/$(LIB)
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > mm.tmp
	mv mm.tmp Makefile

.PHONY: depend
depend: $(SRCS)
	@echo !!! Creating dependencies !!!
	g++ -MM -MP -c -I$(INCLUDE) $(SRCS) > $(LIBDEPEND)
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > mm.tmp
	cat $(LIBDEPEND) >> mm.tmp
	mv mm.tmp Makefile
	rm -f $(LIBDEPEND)

# DO NOT DELETE THIS LINE - make depend uses it
