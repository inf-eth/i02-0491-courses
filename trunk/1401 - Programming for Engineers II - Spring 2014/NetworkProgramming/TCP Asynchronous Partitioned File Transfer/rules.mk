all:
	for dir in $(SUBDIR);\
		do\
			$(MAKE) --directory=$$dir;\
		done
clean:
	for dir in $(SUBDIR);\
		do\
			$(MAKE) --directory=$$dir clean;\
		done
runC:
	$(MAKE) --directory=Client run
runS:
	$(MAKE) --directory=Server run
