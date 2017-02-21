INCLUDE=../../../include
LIB=../../../lib

SRC=log_mgr.cpp
OBJ=$(SRC:.cpp=.o)
LIBNAME=liblog.a

CFLAGS= -c -g -I$(INCLUDE)

all: it

%.o: %.cpp
	g++ $(CFLAGS) $<

it: $(OBJ)
.PHONY: clean

clean:
	rm -f *.o
