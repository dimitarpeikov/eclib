SRCS = $(wildcard *.c)
EXE = eclib_test
TARGET = $(EXE)
LDFLAGS = -L ../eclib -leclib

OBJS = ${SRCS:%.c=%.o}
DEPS = ${SRCS:%.c=%.d}

test:	$(TARGET)
	./$(TARGET)

all:	$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS) *~

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

.c.o:
	$(CC) -I ../ $(CFLAGS) -c -o $@ $<

.c.d:
	$(CC) -M -I ../ $(CFLAGS) -o $@ $<

.PHONY: clean all test
.SUFFIXES: .d

-include $(DEPS)

