SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=client
CC:=gcc
CFLAGS:=-Wall -I../includeClient -I /usr/include/mysql/
$(ELF):$(OBJS)
	gcc $^ -o $@ -lpthread -lmysqlclient
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF)

