#
# Project:    Homework 2
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the test_log executable
#
INCLUDE=../../../include
LIB=../../../lib
BIN=../../../bin
SRC=test_log.c
OBJ=$(SRC:.c=.o)
LIBNAME=log_mgr
EXE=test_log
DEPEND=depend.mk

CC=g++
CFLAGS=-g -I$(INCLUDE)

all: it

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) -L$(LIB) -l$(LIBNAME)

.PHONY: it
it: $(EXE)
	@echo !!! test_log built !!!

.PHONY: install
install: it
	install -C $(EXE) $(BIN)
	@echo !!! test_log installed !!!
.PHONY: clean
clean:
	rm -f *.o *.mk $(EXE) $(BIN)/$(EXE)
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
