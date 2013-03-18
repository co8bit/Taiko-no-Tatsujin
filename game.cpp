#include "game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    midi("")
{
}

void Game::setMidi(Midi new_midi)
{
    midi = new_midi;
}
