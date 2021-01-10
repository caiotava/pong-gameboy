CC = lcc
CFLAGS = -Wa-l -Wl-m -Wl-j
LDFLAGS =
EMULATOR = bgb
EMULATOR_FLAGS =
BIN = pong.gb

all: $(BIN)

run: $(BIN)
	$(EMULATOR) $(EMULATOR_FLAGS) $(BIN)

$(BIN):	pong.o sprites.o render.o game.o collision.o
	$(CC) $(LDFLAGS) -o $(BIN) $^

sprites.o: sprites.c
	$(CC) $(CFLAGS) -c -o sprites.o sprites.c

pong.o: pong.c
	$(CC) $(CFLAGS) -c -o pong.o pong.c

render.o: render.c
	$(CC) $(CFLAGS) -c -o render.o render.c

game.o: game.c
	$(CC) $(CFLAGS) -c -o game.o game.c

collision.o: collision.c
	$(CC) $(CFLAGS) -c -o collision.o collision.c

clean:
	rm -f *.o *.map *.gb *.lst *.asm *.sym