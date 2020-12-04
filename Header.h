#ifndef HEADER
#define HEADER

#include <vector>
#include "Players.h"

int playsingle();

std::vector<int> playmulti();

int playbot();

void extended_scoreboard(Players player1, Players player2, bool mode = 0);

#endif