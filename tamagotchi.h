#ifndef _TAMAGOTCHI_H_
#define _TAMAGOTCHI_H_

#include "state_machine.h"

typedef struct {
	int irq_set_kbd;
	int irq_set_timer;
	int irq_set_mouse;

	unsigned char packet[3]; 

	int intcounter;
	unsigned long scan;

}Game;

Game* startGame();

void interruptHandler(Game* game, States* gameStates);

void leaveGame(Game* game, States* gameStates);

#endif

