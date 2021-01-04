HEADERS = $(wildcard *.h)
PRODUCT_SOURCES = $(wildcard *.c)
PRODUCT_OBJECTS = $(PRODUCT_SOURCES:.c=.o)

CC := /EBS/mount/qqi/build_pure/bin/clang
CFLAGS := -Wall -O1 -g -fopencilk -flto -mllvm -use-external-abi-functions -fno-vectorize -fno-slp-vectorize
EXTRA_CFLAGS :=
LDFLAGS := -flto -fuse-ld=gold -fopencilk -L/efs/home/qqi/cheetah-dev-splitter/runtime/ -static-libopencilk -lprofiler

ifneq ($(ARR_LEN),)
	EXTRA_CFLAGS := -DARR_LEN=$(ARR_LEN) $(EXTRA_CFLAGS)
endif

ifneq ($(VECTOR_LEN),)
	EXTRA_CFLAGS := -DVECTOR_LEN=$(VECTOR_LEN) $(EXTRA_CFLAGS)
endif

all:	$(PRODUCT_OBJECTS)
	$(CC) $(LDFLAGS) -o main $(PRODUCT_OBJECTS)

%.o:		%.c $(HEADERS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o $@ -c $<

clean:
	rm -f main *.o *.s *.ll
