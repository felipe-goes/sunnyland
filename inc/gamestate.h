#ifndef GAMESTATE_INCLUDED
#define GAMESTATE_INCLUDED

// Attributes
typedef enum {Debug, Production} GameState;
extern GameState gameState;

// Functions
extern void changeGameState(GameState state);
extern GameState getGameState(void);

#endif // !GAMESTATE_INCLUDED
