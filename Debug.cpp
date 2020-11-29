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

void Debug::fake_roll(Players &player)
{
	int no_dice = player.no_rolling_dice();
	for (int i = 0; i < no_dice; i++)
	{
		std::cin >> player.dice[i].side;
	}

	player.sort_dice();
	player.print_dice();
	player.update_T_dice();

	player.roll_left--;

	std::cout << "You have " << player.roll_left << " roll(s) left.\n\n";

}
void Debug::debug_play()
{
	Players player1;

	for (int i = 0; i < 13; i++) //13 rounds
	{
		player1.reset_dice();
		player1.roll_left = 3;
		std::cout << "Round " << i + 1 << ":\n\n";
		while (player1.roll_left > 0) //3 rolls a round
		{
			fake_roll(player1);
			player1.print_scoreboard();
			player1.choose_combo();
			/*
			if (i < 12)
			{
				system("pause");
				std::cout << "\n";
			}
			*/
		}
	}
	int score = player1.total_score();
	std::cout << "Your final score is " << score << "!\n\n";
}