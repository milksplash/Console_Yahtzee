#ifndef HEADER
#define HEADER

#include <vector>
#include "Players.h"

int playsingle();

std::vector<int> playmulti();

int playbot();

void extended_scoreboard_new(Players player1, int player1_mode, Players player2, int player2_mode, bool instr = 1);

#endif