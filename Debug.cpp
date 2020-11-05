#include <iostream>
#include <vector>
#include "Debug.h"
#include "Players.h"

void Debug::print_player_dice(std::vector<Players::Dice> dice)
{
	//print vector Player::Dice
	for (int i = 0; i < dice.size(); i++)
	{
		std::cout << dice[i].side << "\t";
	}
	std::cout << "\n";
	for (int i = 0; i < dice.size(); i++)
	{
		std::cout << dice[i].roll_hold << "\t";
	}
	std::cout << "\n\n";
}
void Debug::print_player_scoreboard(std::vector<Players::Scores> scores)
{
	//print vector Player::Score
	for (int i = 0; i < scores.size(); i++)
	{
		std::cout << scores[i].score << "\t";
	}
	std::cout << "\n";
	for (int i = 0; i < scores.size(); i++)
	{
		std::cout << scores[i].taken << "\t";
	}
	std::cout << "\n\n";
}
void Debug::fake_dice(std::vector<Players::Dice> dice, int one, int two, int three, int four, int five)
{
	//debug: set dice face
	dice[0].side = one;
	dice[1].side = two;
	dice[2].side = three;
	dice[3].side = four;
	dice[4].side = five;
}