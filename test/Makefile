BIN = echoo

CC = gcc
CSAPP_INC = ./include
CSAPP_SRC = ./src
CFALGS = -O0 -g -Wall -Werror -I./include -I.
CCFLAGS =
LDFLAGS = -pthread

all: $(BIN)

$(BIN): $(BIN).o $(CSAPP_SRC)/csapp.o
	gcc $(LDFLAGS) -o $(BIN) $(BIN).o $(CSAPP_SRC)/csapp.o 
$(BIN).o:
	gcc -c $(CFLAGS) $(CCFLAGS) -o $(BIN).o $(BIN).c

$(CSAPP_SRC)/csapp.o: $(CSAPP_SRC)/csapp.c $(CSAPP_INC)/csapp.h
	gcc -c $(CFLAGS) $(CCFLAGS) -o $(CSAPP_SRC)/csapp.o $(CSAPP_SRC)/csapp.c

PHONY: run clean

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BIN) $(BIN).o
