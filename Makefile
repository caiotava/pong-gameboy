CC		= lcc
CFLAGS		= -Wa-l -Wl-m -Wl-j
LDFLAGS		=
EMULATOR 	= VisualBoyAdvance
EMULATOR_FLAGS	=
BIN		=pong.gb

all:	$(BIN)

run:	$(BIN)
	$(EMULATOR) $(EMULATOR_FLAGS) $(BIN)

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o:	%.s
	$(CC) $(CFLAGS) -c -o $@ $<

%.s:	%.c
	$(CC) $(CFLAGS) -S -o $@ $<

%.gb:	%.o
	$(CC) $(LDFLAGS) -o $@ $<

clean:
	rm -f *.o *.map *.gb *.lst
