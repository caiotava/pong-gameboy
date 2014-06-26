#include<gb/gb.h>
#include<stdio.h>
#include "sprites.h"
#include "sprites.c"

void init_sprites()
{
	int i = 0;
	SPRITES_8x8;

	set_sprite_data(0, 7, sprites);

	set_sprite_tile(0, 1);
	set_sprite_tile(1, 1);
	set_sprite_tile(2, 1);
	set_sprite_tile(3, 1);
	set_sprite_tile(4, 1);
	move_sprite(i, 5, 5);

	SHOW_SPRITES;
}

void main()
{
	disable_interrupts();
	DISPLAY_OFF;
	//LCDC_REG = 0x67;

	//init_sprites();
	printf("Pong") ;
	DISPLAY_ON;
	enable_interrupts();
}
