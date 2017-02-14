INCLUDE=../../../include
LIBRARY=../../../lib
BIN=../../../bin
EXE=conv_to_cent
SRC=$(EXE).cpp
OBJ=$(SRC:.cpp=.o)
DEPEND=depend.mk

CFLAGS=-g -Wall -I$(INCLUDE) 

all: it

%.o: %.cpp 
	g++ -c $(CFLAGS) $<

it: $(DEPEND) $(OBJ) 
	g++ $(CFLAGS) $(SRC) -o $(EXE) -L$(LIBRARY) -larg -ltemp_conv 

clean:
	rm -f *.o $(EXE) *.mk
	rm -f $(BIN)/$(EXE)

install: it
	install -C -m 775 $(EXE) $(BIN)

depend: $(DEPEND)
 
$(DEPEND): 
	g++ -MM -MP -c -I$(INCLUDE) $(SRC) > $(DEPEND) 

-include $(DEPEND)
