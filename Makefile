CC		= lcc
CFLAGS		= -Wa-l -Wl-m -Wl-j
LDFLAGS		=
EMULATOR 	= VisualBoyAdvance
EMULATOR_FLAGS	=
BIN		=pong.gb

all:	$(BIN)

run:	$(BIN)
	$(EMULATOR) $(EMULATOR_FLAGS) $(BIN)

$(BIN):	pong.o sprites.o render.o engine.o collision.o
	$(CC) $(LDFLAGS) -o $(BIN) $^

sprites.o: sprites.c
	$(CC) $(CFLAGS) -c -o sprites.o sprites.c

pong.o: pong.c
	$(CC) $(CFLAGS) -c -o pong.o pong.c

render.o: render.c
	$(CC) $(CFLAGS) -c -o render.o render.c

engine.o: engine.c
	$(CC) $(CFLAGS) -c -o engine.o engine.c

collision.o: collision.c
	$(CC) $(CFLAGS) -c -o collision.o collision.c

clean:
	rm -f *.o *.map *.gb *.lst
