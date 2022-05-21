CC=gcc
CFLAGS=-I.
LDIR =./lib
DESTDIR=/usr/local
PREFIX=/bin

arameia: arameia.c entity.c level.c animation.c point.c direction.c
	$(CC) -g -o $@ arameia.c entity.c level.c animation.c point.c direction.c -lSDL2 -lSDL2_image

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
