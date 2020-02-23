CC=clang
CFLAGS=-target $(TARGET) -ffreestanding -nostdinc -nostdlib -Iinclude -Wall
AS=clang
AFLAGS=-target $(TARGET)
KERNEL=linux
TARGET=$(ARCH)-none-$(ABI)
ARCH=x86_64
ABI=elf

BUILDDIR=build

LIBC_SRC=$(wildcard src/libc/*.c)
CRT0_SRC=$(wildcard arch/$(TARGET)/crt0/*.s)
SYSCALLS_SRC=$(wildcard arch/$(TARGET)/$(KERNEL)/*.s)

LIBC=$(BUILDDIR)/lib/libc.so
CRT0=$(BUILDDIR)/lib/crt0.o
SYSCALLS=$(BUILDDIR)/lib/syscalls.o

.PHONY: all clean

all: $(LIBC) $(CRT0)

clean:
	rm -rf $(BUILDDIR)

$(BUILDDIR):
	mkdir -p $@/lib

$(LIBC): $(LIBC_SRC) $(SYSCALLS) $(BUILDDIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $(LIBC_SRC) $(SYSCALLS)

$(CRT0): $(CRT0_SRC) $(BUILDDIR)
	$(AS) $(AFLAGS) -fPIC -c -o $@ $(CRT0_SRC)

$(SYSCALLS): $(SYSCALLS_SRC) $(BUILDDIR)
	$(AS) $(AFLAGS) -fPIC -c -o $@ $(SYSCALLS_SRC)

