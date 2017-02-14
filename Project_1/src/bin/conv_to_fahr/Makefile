INCLUDE=../../../include
LIBRARY=../../../lib
BIN=../../../bin
EXE=conv_to_fahr
SRC=$(EXE).cpp
OBJ=$(SRC:.cpp=.o)
DEPEND=depend.mk

CFLAGS=-g -Wall -I$(INCLUDE) 

-include $(DEPEND)

all: it

$(OBJ): $(SRC)
	g++ -c $(CFLAGS) $(SRC)

it:$(DEPEND) $(OBJ) 
	g++ $(CFLAGS) $(SRC) -o $(EXE) -L$(LIBRARY) -larg -ltemp_conv 

clean:
	rm -f *.o $(EXE) *.mk
	rm -f $(BIN)/$(EXE)

install: it
	install -C -m 775 $(EXE) $(BIN)

$(DEPEND): 
	g++ -MM -MP -c -I$(INCLUDE) $(SRC) > $(DEPEND)

depend: $(DEPEND)
