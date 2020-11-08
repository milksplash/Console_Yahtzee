#include <iostream>
#include "Header.h"
#include "Players.h"

int playsingle()
{
	Players player1;
	
	for (int i = 0; i < 13; i++) //13 rounds
	{
		player1.reset_dice();
		player1.roll_left = 3;
		while (player1.roll_left > 0) //3 rolls a round
		{
			std::cout << "Round " << i + 1 << ":\n";
			player1.roll_dice();
			player1.print_scoreboard();
			player1.choose_swap();
			if (i < 12)
			{
				system("pause");
				std::cout << "\n";
			}
		}
	}
	int score = player1.total_score();
	std::cout << "Your final score is " << score << "!\n\n";
	return score;
} 

std::vector<int> playmulti()
{
	Players player1;
	Players player2;
	std::vector<int> scores = { 0, 0 };
	return scores;
}

int playbot()
{
	Players player1;
	Players bot;
	int score = 0;
	return score;
}