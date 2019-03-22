CC=gcc
CFLAGS=-g -Wall -O3 
LDFLAGS=-lwiringPi -lrt -lcrypt -lm
#LDLIBS=-lwiringPi

all: piTankGo

#OBJS=kbhit.o fsm.o piTankGo_1.o player.o tmr.o torreta.o
OBJS=kbhit.o fsm.o piTankGo_1.o tmr.o torreta.o

piTankGo: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	$(RM) *.o *~ piTankGo


