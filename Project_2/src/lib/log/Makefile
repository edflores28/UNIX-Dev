INCLUDE=../../../include
LIB=../../../lib

SRC=log_mgr.cpp
OBJ=$(SRC:.cpp=.o)
LIBNAME=liblog.a

CFLAGS= -c -g -I$(INCLUDE)

all: it

%.o: %.cpp
	g++ $(CFLAGS) $<

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

.PHONY: it
it: $(LIBNAME)

install: it
	install -C -m 775 $(LIBNAME) $(LIB)

.PHONY: clean
clean:
	rm -f *.o *.a $(LIB)/$(LIBNAME)
