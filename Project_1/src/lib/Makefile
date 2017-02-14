ARGDIR=./arg
TEMPCONVDIR=./temp_conv

it:
	$(MAKE) -C $(ARGDIR) it
	$(MAKE) -C $(TEMPCONVDIR) it

clean:
	$(MAKE) -C $(ARGDIR) clean
	$(MAKE) -C $(TEMPCONVDIR) clean 
	
install: 
	$(MAKE) -C $(ARGDIR) install
	$(MAKE) -C $(TEMPCONVDIR) install

depend: 
	$(MAKE) -C $(ARGDIR) depend
	$(MAKE) -C $(TEMPCONVDIR) depend 
