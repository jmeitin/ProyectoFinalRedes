CC=g++
CFLAGS=-g -I.
DEPS = Socket.h Message.h Server.h
OBJ = Socket.o Message.o Server.o
LIBS=-lpthread

%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

all: cs cc

cs: $(OBJ) Host.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

cc: $(OBJ) Player.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o cs cc

