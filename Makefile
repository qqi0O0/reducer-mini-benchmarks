HEADERS = $(wildcard *.h)
PRODUCT_SOURCES = $(wildcard *.c)
PRODUCT_OBJECTS = $(PRODUCT_SOURCES:.c=.o)

CC := /home/ubuntu/opencilk/build/bin/clang
CFLAGS := -Wall -O3 -g -fopencilk -flto -fno-vectorize -fno-slp-vectorize -I/home/ubuntu/cheetah-dev/include
EXTRA_CFLAGS :=
LDFLAGS := -flto -fuse-ld=gold -fopencilk -L/home/ubuntu/cheetah-dev/runtime -static-libopencilk

ifneq ($(VECTOR_LEN),)
	EXTRA_CFLAGS := -DVECTOR_LEN=$(VECTOR_LEN) $(EXTRA_CFLAGS)
endif

ifneq ($(METHOD),)
	EXTRA_CFLAGS := -DMETHOD=$(METHOD) $(EXTRA_CFLAGS)
endif

all:	$(PRODUCT_OBJECTS)
	$(CC) $(LDFLAGS) -o main $(PRODUCT_OBJECTS)

%.o:		%.c $(HEADERS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o $@ -c $<

clean:
	rm -f main *.o *.s *.ll
