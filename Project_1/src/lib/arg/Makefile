#
# Project:    Homework 1
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the arg library
#
INCLUDE=../../../include
LIBDIR=../../../lib
SRCS=getarg.cpp
OBJ=$(SRCS:.cpp=.o)
LIB=libarg.a
LIBDEPEND=depend.mk

CFLAGS=-c -g -I$(INCLUDE)

all: it

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

%.o: %.cpp
	g++ $(CFLAGS) $<

.PHONY: it
it: $(LIB)

.PHONY: install
install: it
	install -c -m 666 $(LIB) $(LIBDIR)

.PHONY: clean
clean:
	rm -f *.o *.a *.mk
	rm -f $(LIBDIR)/$(LIB)
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > mm.tmp
	mv mm.tmp Makefile

.PHONY: depend
depend: $(SRCS)
	g++ -MM -MP -c -I$(INCLUDE) $(SRCS) > $(LIBDEPEND)
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > mm.tmp
	cat $(LIBDEPEND) >> mm.tmp
	mv mm.tmp Makefile
	rm -f $(LIBDEPEND)

# DO NOT DELETE THIS LINE - make depend uses it
