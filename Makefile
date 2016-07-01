



all: showhex


showhex: showhex.c
	cc -o $@ $^

clean:
	rm -fr showhex

install:
	cp -af showhex /usr/local/bin/
distclean: clean
	rm -fr /usr/local/bin/showhex
