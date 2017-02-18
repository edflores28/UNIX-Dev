#
# Project:    Homework 1
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Makefile that creates the conv_to_fahr executable
#
INCLUDE=../../../include
LIBRARY=../../../lib
BIN=../../../bin
EXE=conv_to_fahr
SRC=$(EXE).cpp
OBJ=$(SRC:.cpp=.o)
DEPEND=depend.mk

CFLAGS=-g -Wall -I$(INCLUDE) 

all: it

$(OBJ): $(SRC)
	g++ -c $(CFLAGS) $(SRC)

.PHONY: it
it: $(OBJ) 
	g++ $(CFLAGS) $(SRC) -o $(EXE) -L$(LIBRARY) -larg -ltemp_conv 

.PHONY: clean
clean:
	rm -f *.o $(EXE) *.mk
	rm -f $(BIN)/$(EXE)
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > mm.tmp
	mv mm.tmp Makefile

.PHONY: install
install: it
	install -C -m 775 $(EXE) $(BIN)

.PHONY: depend
depend: $(SRCS)
	g++ -MM -MP -c -I$(INCLUDE) $(SRC) > $(DEPEND)
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > mm.tmp
	cat $(DEPEND) >> mm.tmp
	mv mm.tmp Makefile
	rm -f $(DEPEND)

# DO NOT DELETE THIS LINE - make depend uses it
conv_to_fahr.o: conv_to_fahr.cpp ../../../include/fahr_convert.h

../../../include/fahr_convert.h:
