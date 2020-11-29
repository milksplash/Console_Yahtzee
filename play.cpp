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
		std::cout << "Round " << i + 1 << ":\n\n";
		while (player1.roll_left > 0) //3 rolls a round
		{
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

	for (int i = 0; i < 13; i++)
	{
		player1.reset_dice();
		player2.reset_dice();
		player1.roll_left = 3;
		player2.roll_left = 3;
		std::cout << "Round " << i + 1 << ":\n\n";

		std::cout << "Player 1's turn:\n\n";
		while (player1.roll_left > 0)
		{
			player1.roll_dice();

			player1.print_scoreboard(1);
			extended_scoreboard(player1, player2, 0);

			player1.choose_swap();

			if (i < 12)
			{
				system("pause");
				std::cout << "\n";
			}
		}

		std::cout << "Player 2's turn:\n\n";
		while (player2.roll_left > 0)
		{
			player2.roll_dice();

			player2.print_scoreboard(1);
			extended_scoreboard(player1, player2, 1);

			player2.choose_swap();

			if (i < 12)
			{
				system("pause");
				std::cout << "\n";
			}
		}
	}
	scores[0] = player1.total_score();
	scores[1] = player2.total_score();
	std::cout << "Player 1 got a score of " << scores[0] << " and Player 2 got a score of " << scores[1] << ".\n";
	std::cout << "Player " << ((scores[0] < scores[1] ? 2 : 1)) << " win!\n\n";
	return scores;
}

int playbot()
{
	Players player1;
	Players bot;
	int score = 0;
	return score;
}

void extended_scoreboard(Players player1, Players player2, bool mode)
{
	/*
	scoreboard plugin to modify scoreboard for use of multiplayer
	mode 0 = Player 1 is in control
	mode 1 = Player 2 is in control
	*/
	std::cout << "P1\t";
	player1.print_scoreboard_values(mode);
	std::cout << player1.total_score() << "\n";
	std::cout << "P2\t";
	player2.print_scoreboard_values(!mode);
	std::cout << player2.total_score() << "\n\n<0>: toggle between selecting die and choosing combination\n<14>: roll die(s)\n\n";
}