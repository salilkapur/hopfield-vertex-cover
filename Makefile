CC=gcc
INCLUDE_DIRS=.
CFLAGS= -Wall -g -I$(INCLUDE_DIRS) -std=c99

HEADERS=$(wildcard *.h)
SRCS=$(wildcard *.c)
OBJS=io_utility.o graph.o hnn.o mvc.o
DOBJS=$(addprefix $(OBJDIR)/, $(OBJS))
OBJDIR=./obj

$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o : %.c $(HEADERS) 
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(DOBJS)
	$(CC) -o mvc $(DOBJS) $(CFALGS)

clean:
	rm -f mvc $(OBJDIR)/*.o *~
