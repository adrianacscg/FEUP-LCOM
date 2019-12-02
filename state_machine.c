#include "state_machine.h"

States* newGameStates() {
	States* gameStates = (States*) malloc(sizeof(States));

	gameStates->gameState = LOADING;
	gameStates->optGame = INIT_OPT;
  gameStates->miniGame = INIT_GAME;

	return gameStates;
}

void check_game(game evt, States* gameStates) {

	switch (gameStates->gameState) {

	case LOADING:
		if (evt == INIT_OPT)
			gameStates->gameState = CHOOSE;
    break;

	case CHOOSE:
		if (evt == CHOSEN)
			gameStates->gameState = PLAY;
    break;

	case PLAY:
		if (evt == EAT_EVT)
			gameStates->gameState = EAT;
		else if (evt == SLEEP_EVT)
			gameStates->gameState = SLEEP;
    else if (evt == MINI_GAME_OPT)
    {
      gameStates->gameState = MINI_GAME;
      gameStates->miniGame = INIT_GAME;
    }
    break;

	case EAT:
		if (evt == ATE)
			gameStates->gameState = PLAY;
    break;
  
  case SLEEP:
    if (evt == SLEPT)
      gameStates->gameState = PLAY;
		break;
  
  case COMP:
    break;

	default:
		break;
	}

	return;
}

void check_mini_game(options_inside_mini_game evt, States* gameStates) {

	switch (gameStates->movements) {

	case LEFT:
		gameStates->miniGame = MID;
    break;

	case RIGHT:
		gameStates->miniGame = MID;
    break;

  case WRONG_LEFT:
		gameStates->miniGame = END;
    break;

	case WRONG_RIGHT:
		gameStates->miniGame = END;
    break;

	default:
		break;
	}

	return;
}

void deleteGameStates(States* gameStates) {
	free(gameStates);
	return;
}