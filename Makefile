CC=clang
CFLAGS=-Wall -g -nostdinc -ffreestanding -nostdlib -fPIC -Iinclude
AWK=awk

ARCH=x86_64
SYSCALL_ABI=syscalls-abi/linux-v5.4-rc5
BUILDDIR=build

CRT0_SRC=arch/$(ARCH)/crt0/crt0.s
SYSCALLS_SRC=arch/$(ARCH)/syscalls/syscalls.s
LIBC_SRC=$(wildcard src/libc/*.c)
HELLO_SRC=$(wildcard src/hello/*.c)

CRT0=$(BUILDDIR)/obj/crt0.o
SYSCALLS=$(BUILDDIR)/obj/syscalls.o
LIBC=$(BUILDDIR)/lib/libc.so
HELLO=$(BUILDDIR)/bin/hello

.PHONY: all clean

all: $(HELLO)

clean:
	rm -rf $(BUILDDIR) $(SYSCALLS_SRC)

$(BUILDDIR):
	mkdir -p $@/bin $@/lib $@/obj

$(CRT0): $(CRT0_SRC) $(BUILDDIR)
	$(CC) -fPIC -c -o $@ $<

$(SYSCALLS_SRC): $(SYSCALL_ABI)
	$(AWK) -f tools/syscalls.awk < $< > $@

$(SYSCALLS): $(SYSCALLS_SRC) $(BUILDDIR)
	$(CC) -fPIC -c -o $@ $<

$(LIBC): $(LIBC_SRC) $(SYSCALLS) $(BUILDDIR)
	$(CC) $(CFLAGS) -shared -o $@ $(LIBC_SRC) $(SYSCALLS)

$(HELLO): $(HELLO_SRC) $(CRT0) $(LIBC) $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $(HELLO_SRC) $(CRT0) $(LIBC)

