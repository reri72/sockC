CC = gcc
CFLAGS = -Wall -fPIC
TARGET_STATIC = libsockC.a
TARGET_SHARED = libsockC.so

SRCS = sockTcp.c 
OBJS = $(SRCS:.c=.o)

all: $(TARGET_STATIC) $(TARGET_SHARED)

static: $(TARGET_STATIC)

shared: $(TARGET_SHARED)

$(TARGET_STATIC): $(OBJS)
	ar rcs $@ $^

$(TARGET_SHARED): $(OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c %.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET_STATIC) $(TARGET_SHARED)