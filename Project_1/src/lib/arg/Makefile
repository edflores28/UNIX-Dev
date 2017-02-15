INCLUDE=../../../include
LIBDIR=../../../lib
SRCS=getarg.cpp
OBJ=$(SRCS:.cpp=.o)
LIB=libarg.a
LIBDEPEND=depend.mk

CFLAGS=-c -g -I$(INCLUDE)

-include $(LIBDEPEND)

.PHONY: clean

all: it

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

%.o: %.cpp
	g++ $(CFLAGS) $<

it: $(LIBDEPEND) $(LIB)

install: it
	install -c -m 666 $(LIB) $(LIBDIR)

$(LIBDEPEND):
	g++ -MM -MP -c -I$(INCLUDE) $(SRCS) > $(LIBDEPEND)

depend: $(LIBDEPEND)

clean:
	rm -f *.o *.a *.mk
	rm -f $(LIBDIR)/$(LIB)
