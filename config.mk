# wall2pnm version
VERSION = 0.1

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# includes and libs
INCS = -I. -I/usr/include -I${X11INC}
LIBS = -L/usr/lib -lc -lcrypt -L${X11LIB} -lX11 -lXext

# flags
CPPFLAGS = -DVERSION=\"$(VERSION)\" -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600
CFLAGS = -Wall -Wno-format-truncation -pedantic -std=c99 ${INCS} ${CPPFLAGS}
LDFLAGS = -s ${LIBS}
STCFLAGS = $(CPPFLAGS) $(CFLAGS)
STLDFLAGS = $(LDFLAGS)

# compiler and linker
CC = gcc
