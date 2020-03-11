TARGET		 = logjudge
OBJS	   	:= $(patsubst %.c, %.o, $(wildcard src/*.c))
OUTDIR		:= out
CC		   	?= gcc
CCFLAGS	   	+= -std=c11 -O1 -DOUT_DIR='"$(OUTDIR)"'

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	$(RM) $(wildcard src/*.o) $(TARGET)

.PHONY:
	clean