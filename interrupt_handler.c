#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "tamagotchi.h"
#include "keyboard.h"
#include "video_card.h"
#include "i8254.h"
#include "macros_kbd.h"
#include "ps2_mouse_macros.h"

void kbdManager(Game* game, States* gameStates) {

	if (gameStates->gameState == LOADING)
		if (game->scan == ENTER_BREAK_CODE)
			check_game(LOADING, gameStates);

}