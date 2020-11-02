HEADERS = $(wildcard *.h)
PRODUCT_SOURCES = $(wildcard *.c)
PRODUCT_OBJECTS = $(PRODUCT_SOURCES:.c=.o)

CC := /EBS/mount/qqi/build/bin/clang
CFLAGS := -Wall -O3 -g -fopencilk -flto -mllvm -use-external-abi-functions
LDFLAGS := -flto -fuse-ld=gold -fopencilk -L/efs/home/qqi/cheetah-dev/runtime/ -static-libopencilk

all:	$(PRODUCT_OBJECTS)
	$(CC) $(LDFLAGS) -o main $(PRODUCT_OBJECTS)

%.o:		%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f main *.o
