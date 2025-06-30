CC=gcc
CFLAGS=-Wall -Wextra -Iinclude
SRC=src/main.c src/linkOps.c src/utils.c
OUT=linkerr

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
