
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

typedef enum {
	LOADING, CHOOSE, PLAY, MINI_GAME, EAT, SLEEP, COMP
}game;

typedef enum {
	INIT_OPT, CHOSEN, ATE, SLEPT, MINI_GAME_OPT, EAT_EVT, SLEEP_EVT
}options_inside_game;

typedef enum {
	INIT_GAME, MID, END
}mini_game;

typedef enum{
	WRONG_LEFT, WRONG_RIGHT, LEFT, RIGHT
}options_inside_mini_game;

typedef struct {
	game gameState;
  options_inside_game optGame;
  mini_game miniGame;
	options_inside_mini_game movements;
} States;

void check_game(game evt, States* gameStates);
void check_mini_game(options_inside_mini_game evt, States* gameStates);
void deleteGameStates(States* gameStates);

#endif
