#
# Project:    Homework 2
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the log library
#
INCLUDE=../../../include
LIB=../../../lib

SRC=log_mgr.cpp
OBJ=$(SRC:.cpp=.o)
LIBNAME=liblog_mgr.a
DEPEND=depend.mk

CFLAGS= -c -g -I$(INCLUDE)

all: it

%.o: %.cpp
	g++ $(CFLAGS) $<

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

.PHONY: it
it: $(LIBNAME)
	@echo !!! log library built !!

install: it
	install -C -m 775 $(LIBNAME) $(LIB)
	@echo !!! log library installed !!

.PHONY: clean
clean:
	rm -f *.o *.a *.mk $(LIB)/$(LIBNAME)
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > mm.tmp
	mv mm.tmp Makefile
	@echo !!! Directories cleaned !!!

.PHONY: depend
depend: $(SRCS)
	g++ -MM -MP -c -I$(INCLUDE) $(SRC) > $(DEPEND)
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > mm.tmp
	cat $(DEPEND) >> mm.tmp
	mv mm.tmp Makefile
	rm -f $(DEPEND)
	@echo !!! Dependencies created !!!

# DO NOT DELETE THIS LINE - make depend uses it
