#include "../inc/gamestate.h"

GameState gameState = Debug;

void changeGameState(GameState state) { gameState = state; }

GameState getGameState() { return gameState; }
