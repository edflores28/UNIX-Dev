#
# Project:    Homework 2
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the app2 executable
#
INCLUDE=../../../include
LIB=../../../lib
BIN=../../../bin
SRC=app2.cpp
OBJ=$(SRC:.cpp=.o)
LIBNAMES=-lthread_mgr -llog_mgr -larg
EXE=app2
DEPEND=depend.mk

CC=g++
CFLAGS=-g -Wall -I$(INCLUDE)

all: it

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -pthread -L$(LIB) $(SRC) -o $(EXE) $(LIBNAMES)

.PHONY: it
it: $(EXE)
	@echo !!! $(EXE) built !!!

.PHONY: install
install: it
	install -C $(EXE) $(BIN)
	@echo !!! $(EXE) installed !!!
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
