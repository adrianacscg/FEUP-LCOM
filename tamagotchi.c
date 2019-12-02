#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "tamagotchi.h"
#include "timer.h"
#include "keyboard.h"
#include "mouse.h"
#include "ps2_mouse_macros.h"
#include "state_machine.h"

Game* startGame() {
	Game* game = (Game*) malloc(sizeof(Game));
  uint8_t bit_nokbd, bit_notimer, bit_nomouse;
	game->irq_set_timer = timer_subscribe_int(&bit_notimer);
	game->irq_set_mouse = mouse_subscribe_int(&bit_nomouse);
  mouse_enable_datarp();
	game->irq_set_kbd = kbd_subscribe_int(&bit_nokbd);

	game->intcounter = 0;
	game->scan = 0;

	return game;
}

void interruptHandler(Game* game, States* gameStates) {
	int ipc_status;
	message msg;
	int r;

	while (gameStates->gameState != COMP) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			return;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.m_notify.interrupts & game->irq_set_timer) {

				}

				if (msg.m_notify.interrupts & game->irq_set_kbd) { /* subscribed interrupt */
					game->scan = read_kbd();
					kbdManager(game, gameStates);
				}

				if (msg.m_notify.interrupts & game->irq_set_mouse) {
          
				}

				break;
			default:
				break; /* no other notifications expected: do*/
			}
		}
	}

	return;
}

void deleteBitmaps(Game* game) {

	return;
}

void leaveGame(Game* game, States* gameStates) {

	timer_unsubscribe_int();
	kbd_unsubscribe_int();
	mouse_unsubscribe_int();

	deleteBitmaps(game);
	deleteGameStates(gameStates);

	free(game);

	return;
}

