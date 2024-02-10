NASM = nasm
CC = gcc
CPPFLAGS = -nostdinc -Iinclude
CFLAGS = -Wall -Wextra -fno-PIC -fno-stack-protector -fno-builtin
# CFLAGS += -g -O0

.PHONY: all clean pack

SRCS = syscall.c \
       process/exit.c \
       mm/malloc.c mm/mmap.c mm/mem_list.c \
       string/string.c \
       stat/fstatat.c stat/fstat.c stat/stat.c \
       io/open.c io/close.c io/read_write.c \
       io/lseek.c io/truncate.c io/ftruncate.c \
       errno.c \
       crt/__libc_start_main.c \
       io/puts.c \
       process/nanosleep.c \
       process/sleep.c

OBJS = $(patsubst %.c,%.o,$(SRCS))

all: libc.a

libc.a: $(OBJS) crt/start.o
	$(AR) -rc $@ $^

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

crt/start.o: crt/start.asm
	$(NASM) -f elf64 -o $@ $<

pack: clean
	zip -r ../src.zip *

clean:
	-rm -f *~
	-rm -f $(OBJS) crt/start.o
	-rm -f libc.a