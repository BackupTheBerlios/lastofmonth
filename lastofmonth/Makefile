################################################################################
# Makefile for lastofmonth
################################################################################
# Copyright (C) drueeke.net
################################################################################
# $Id: Makefile,v 1.1 2003/11/04 16:58:52 sauerlaender Exp $
################################################################################

CC = gcc
CFLAGS = -Wall
PROGRAM = lastofmonth
TARGETDIR = /usr/local/$(PROGRAM)

lastofmonth: src/lastofmonth.c
	$(CC) $(CFLAGS) -o $(PROGRAM) src/lastofmonth.c

install: $(PROGRAM)
	install -m 0755 -d $(TARGETDIR)/bin
	install -m 0555 -s $(PROGRAM) $(TARGETDIR)/bin/$(PROGRAM)
	ln -s $(TARGETDIR)/bin/$(PROGRAM) /usr/local/bin/$(PROGRAM)

uninstall: /usr/local/bin/$(PROGRAM)
	rm -f /usr/local/bin/$(PROGRAM)
	rm -rf $(TARGETDIR)

clean:
	rm -f *.o build/$(PROGRAM)
