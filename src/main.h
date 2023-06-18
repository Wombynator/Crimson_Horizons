#ifndef MAIN_H
#define MAIN_H

enum class GameStates
{
    Initializing,
    MainMenu,
    Loading,
    InGame,
    Exiting
};

extern GameStates currentGameState;

void StartMainMenu();
void StartLoading();
void StartGameplay();
void QuitGame();

#endif