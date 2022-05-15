CC=gcc
CFLAGS=-I.
LDIR =./lib
DESTDIR=/usr/local
PREFIX=/bin

arameia: arameia.c entity.c
	$(CC) -o $@ arameia.c entity.c level.c -lSDL2

.PHONY: clean install

install:
	mkdir -p $(DESTDIR)$(PREFIX)
	install -m 755 arameia $(DESTDIR)$(PREFIX)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/arameia

clean:
	rm arameia

.PHONY: clean install uninstall
# vim: tabstop=2 shiftwidth=2 noexpandtab
