DEBUG = 0

CC = gcc
EXEC = ms2tlen
#COMMON = -I./libmseed/ -I.
COMMON = -I/usr/local/ -I.
CFLAGS =  -Wall
#LDFLAGS = -L./libmseed -Wl,-rpath,./libmseed
#LDLIBS = -Wl,-Bstatic -lmseed -Wl,-Bdynamic -lm
LDFLAGS = -L/usr/local
LDLIBS = -lmseed -lm

OBJS = main.o time_length.o

ifeq ($(DEBUG), 1)
CFLAGS += -O0 -g -DDEBUG=1
endif

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	#$(MAKE) -C libmseed/ static
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

clean:
	#$(MAKE) -C libmseed/ clean
	rm -rf $(OBJS) $(EXEC)
