SRCS = $(wildcard *.c)
EXE = calendar_test
TARGET = $(EXE)
LDFLAGS = -L ../eclib -L ../calendar -leclib -lcalendar

OBJS = ${SRCS:%.c=%.o}
DEPS = ${SRCS:%.c=%.d}

execute:	$(TARGET) $(DEPS)
	./$(TARGET)
all:	$(TARGET) $(DEPS)
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS) *~

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

.c.o:
	$(CC) -I ../ $(CFLAGS) -c -o $@ $<

.c.d:
	$(CC) -M -I ../ $(CFLAGS) -o $@ $<

.PHONY: clean all execute
.SUFFIXES: .d

-include $(DEPS)
