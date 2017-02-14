INCLUDE=../../../include
LIBDIR=../../../lib
SRCS=cent_convert.cpp fahr_convert.cpp
OBJ=$(SRCS:.cpp=.o)
LIB=libtemp_conv.a
LIBDEPEND=depend.mk

CFLAGS=-c -g -Wall -I$(INCLUDE)

-include $(LIBDEPEND)

all: it

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

%.o: %.cpp 
	g++ $(CFLAGS) $< 

it: $(LIBDEPEND) $(LIB)

install: it
	install -c -m 666 $(LIB) $(LIBDIR)

depend: $(LIBDEPEND)

$(LIBDEPEND):
	g++ -MM -MP -c -I$(INCLUDE) $(SRCS) > $(LIBDEPEND)

clean:
	rm -f *.o *.a *.mk
	rm -f $(LIBDIR)/$(LIB)
