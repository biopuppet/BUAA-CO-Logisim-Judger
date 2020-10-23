TARGET		 = logjudge
OBJS	   	:= $(patsubst %.c, %.o, $(wildcard *.c))
CC		   	:= gcc
CCFLAGS	 	+= -Wall -O3 -DNDEBUG

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	$(RM) $(wildcard *.o) $(TARGET)

.PHONY: clean