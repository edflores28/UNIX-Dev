INCLUDE=../../include
LIB=../../lib

SRC=test_log.c
OBJ=$(SRC:.c=.o)
LIBNAME=log
EXE=test_log

CC=g++
CFLAGS=-g -I$(INCLUDE)

all: it

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $< -L$(LIB) -l$(LIBNAME)

it: $(EXE)
.PHONY: clean

clean:
	rm -f *.o $(EXE)
