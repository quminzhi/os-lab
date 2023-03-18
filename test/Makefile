BIN = wait

CC = gcc
CFALGS = -O0 -g -Wall -Werror
CCFLAGS =
LDFLAGS =

all: $(BIN)

$(BIN): $(BIN).o
	gcc $(LDFLAGS) -o $(BIN) $(BIN).o

$(BIN).o:
	gcc -c $(CFLAGS) $(CCFLAGS) -o $(BIN).o $(BIN).c

PHONY: run clean

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BIN) $(BIN).o
