#include <iostream>
#include "Header.h"
#include "Players.h"

int playsingle()
{
	Players player1;
	
	for (int i = 0; i < 13; i++)
	{
		player1.reset_dice();
		player1.roll_left = 3;
		std::cout << "Round " << i + 1 << ":\n\n";
		while (player1.roll_left > 0)
		{
			player1.roll_dice();
			switch (player1.yahtzee_check_new())
			{
			case 0:
				player1.print_scoreboard_new();
				player1.choose_swap();
				break;
			case 1:
				system("pause");
				break;
			case 2:
				player1.choose_combo(1);
				break;
			}
			system("pause");
			std::cout << "\n";
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
			switch (player1.yahtzee_check_new(1))
			{
			case 0:
				player1.print_scoreboard_new(1, 1, 0);
				extended_scoreboard_new(player1, 0, player2, 1, 1);
				player1.choose_swap();
				break;
			case 11:
				extended_scoreboard_new(player1, 1, player2, 1, 0);
				system("pause");
				break;
			case 21:
				extended_scoreboard_new(player1, 2, player2, 1, 1);
				player1.choose_combo(1);
				break;
			}
			system("pause");
			std::cout << "\n";
		}

		std::cout << "Player 2's turn:\n\n";
		while (player2.roll_left > 0)
		{
			player2.roll_dice();
			switch (player2.yahtzee_check_new(1))
			{
			case 0:
				player2.print_scoreboard_new(1, 1, 0);
				extended_scoreboard_new(player1, 1, player2, 0, 1);
				player2.choose_swap();
				break;
			case 11:
				extended_scoreboard_new(player1, 1, player2, 1, 0);
				system("pause");
				break;
			case 21:
				extended_scoreboard_new(player1, 1, player2, 2, 1);
				player2.choose_combo(1);
				break;
			}
			system("pause");
			std::cout << "\n";
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

void extended_scoreboard_new(Players player1, int player1_mode, Players player2, int player2_mode, bool instr)
{
	/*
	mode 0: display potential scores
	mode 1: do not display potential scores
	mode 2: multiple yahtzee superset mode
	instr 0: do not show instructions
	instr 1: do show instructions
	*/

	std::cout << "P1\t";
	player1.print_scoreboard_values(player1_mode);
	std::cout << player1.total_score() << "\n";

	std::cout << "P2\t";
	player2.print_scoreboard_values(player2_mode);
	std::cout << player2.total_score();

	if (instr == 1)
	{
		std::cout << "\n\n<0>: toggle between selecting die and choosing combination\n<14>: roll die(s)";
	}
	std::cout << "\n\n";
}