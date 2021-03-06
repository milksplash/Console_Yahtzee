#ifndef DEBUG
#define DEBUG

#include "Players.h"

class Debug
{
public:
	void print_player_dice(std::vector<Players::Dice> dice);
	void print_player_scoreboard(std::vector<Players::Scores> scores);
	void fake_dice(std::vector<Players::Dice> dice, int one, int two, int three, int four, int five);
};

#endif