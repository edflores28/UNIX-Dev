INCLUDE=../../../include
LIBRARY=../../../lib
BIN=../../../bin
EXE=conv_to_cent
SRC=$(EXE).cpp
OBJ=$(SRC:.cpp=.o)
LIBDEPEND=depend.mk

CFLAGS=-g -Wall -I$(INCLUDE) 

$(OBJ): $(SRC)
	g++ -c $(CFLAGS) $(SRC)

it: $(OBJ) 
	g++ $(CFLAGS) $(SRC) -o $(EXE) -L$(LIBRARY) -larg -ltemp_conv 

clean:
	rm -f *.o $(EXE)
	rm -f $(BIN)/$(EXE)

install: it
	install -C -m 775 $(EXE) $(BIN)

depend: 
	g++ -MM -MP -c -I$(INCLUDE) $(SRC) > $(LIBDEPEND) 
