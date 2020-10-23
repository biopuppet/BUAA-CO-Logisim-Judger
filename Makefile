TARGET		 = logjudge
OBJS	   	:= $(patsubst %.c, %.o, $(wildcard src/*.c))
CC		   	:= gcc
CCFLAGS	 	+= -Wall -O3 -DNDEBUG

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	$(RM) $(wildcard src/*.o) $(TARGET)

.PHONY: clean