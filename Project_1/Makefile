LIB=./src/lib
BIN=./src/bin

TEMPCONV=./lib/libtempconv.a
ARG=./lib/libarg.a

$(TEMPCONV):

$(ARG):

lib: $(TEMPCONV) $(ARG)
	$(MAKE) -C $(LIB) install
	

it: lib
	$(MAKE) -C $(LIB) it
	$(MAKE) -C $(BIN) it

clean:
	$(MAKE) -C $(LIB) clean
	$(MAKE) -C $(BIN) clean 
	
install: 
	$(MAKE) -C $(LIB) install
	$(MAKE) -C $(BIN) install

depend: 
	$(MAKE) -C $(LIB) depend
	$(MAKE) -C $(BIN) depend 
