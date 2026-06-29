CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = src/main.c src/graph.c
OUT = rota-estelar

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)

.PHONY: all run clean
