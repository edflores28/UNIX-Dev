#
# Project:    Homework 4
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the install_data executable
#
PRJ_ROOT=../../../
INCLUDE=$(PRJ_ROOT)include
LIB=$(PRJ_ROOT)lib
BIN=$(PRJ_ROOT)bin

EXE=install_data
SRC=$(EXE).cpp
OBJ=$(SRC:.cpp=.o)

LIBNAMES=-lshmlib
DEPEND=depend.mk
STD=-std=c++0x
CC=g++

CFLAGS=$(STD) -g -Wall -I$(INCLUDE)

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
