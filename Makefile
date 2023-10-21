CC = gcc
CFLAGS = -Wall -std=c99 -g
SRC = main.c reading.c stack.c list.c gravity.c 
OBJ = $(SRC:.c=.o)
EXECUTABLE = tileblaster

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)