# vim: sw=8 ts=8

CC	=gcc -pipe --std=gnu99
MODE	=
CFLAGS	=-Os -Wall -pedantic `getconf LFS_CFLAGS` -g
LDFLAGS	=${MODE} `getconf LFS_LDFLAGS` -g
LDLIBS	=-lfuse -ldl

SPROF	=sprof
SPROFARGS=-q

.SUFFIXES:	.s

%.s:	%.o
	objdump -dS $< >$@

all:	example liboverloader.so

liboverloader.so: overloader.c
	${CC} -shared -o $@ ${CFLAGS} $^

clean:
	${RM} a.out *.o core.* lint tags *.s
	${RM} example

distclean clobber: clean
	${RM} liboverloader.so

check:	example liboverloader.so
	LD_LIBRARY_PATH=${PWD} LD_PRELOAD=liboverloader.so ./example
