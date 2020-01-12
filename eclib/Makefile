SRCS = $(wildcard *.c)
LIB = eclib
TARGET = lib$(LIB).a

OBJS = ${SRCS:%.c=%.o}
DEPS = ${SRCS:%.c=%.d}

all:	$(TARGET)
clean:
	$(RM) $(TARGET) $(OBJS) *~

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $+

.c.o:
	$(CC) -I ../ $(CFLAGS) -c -o $@ $<

.c.d:
	$(CC) -M -I ../ $(CFLAGS) -o $@ $<
	
test:

.PHONY: clean all test
.SUFFIXES: .d

-include $(DEPS)

