SUBDIRS = src


all:
	for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir || exit 1; \
	done
	
	test -d DB || mkdir DB

clean:
	-for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir clean || exit 1; \
	done
	-rm -f core

doc:
	doxygen Doxygen
	rm -rf latex

