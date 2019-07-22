SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=server
CC:=gcc
CFLAGS:=-Wall -I../includeServer -I /usr/include/mysql/
$(ELF):$(OBJS)
	gcc $^ -o $@ -lpthread -lmysqlclient
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF)

