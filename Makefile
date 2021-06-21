.POSIX:

include config.mk

SRC = wall2pnm.c
OBJ = $(SRC:.c=.o)

all: options wall2pnm

options:
	@echo wall2pnm build options:
	@echo "VERSION = $(VERSION)"
	@echo "CFLAGS  = $(STCFLAGS)"
	@echo "LDFLAGS = $(STLDFLAGS)"
	@echo "CC      = $(CC)"

.c.o:
	@echo CC $<
	@$(CC) $(STCFLAGS) -c $<

${OBJ}: config.mk

wall2pnm: $(OBJ)
	@echo CC -o $@
	@$(CC) -o $@ $(OBJ) $(STLDFLAGS)

clean:
	@echo cleaning
	@rm -f wall2pnm $(OBJ)

install: wall2pnm
	@echo installing executables to ${PREFIX}/bin
	@mkdir -p ${PREFIX}/bin
	@cp -f wall2pnm ${PREFIX}/bin
	@chmod 755 ${PREFIX}/bin/wall2pnm

uninstall:
	@echo removing executable files from ${PREFIX}/bin
	@rm -f ${PREFIX}/bin/wall2pnm

.PHONY: all options clean install uninstall
