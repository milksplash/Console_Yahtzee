#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Leaderboard.h"
#include "Utility.h"

void Leaderboard::get()
{
	if (read_error("leaderboard.txt"))
	{
		std::cout << "Leaderboard file cannot be accessed. Use \"Reset Leaderboard\" to create a new one.\n\n";
		return;
	}
	std::ifstream readfrom("leaderboard.txt");
	for (int i = 0; i < 5; i++)
	{
		readfrom >> vector_leaderboard[i].name >> vector_leaderboard[i].score;
	}
	readfrom.close();
}
void Leaderboard::print()
{
	if (read_error("leaderboard.txt"))
	{
		std::cout << "Leaderboard file cannot be accessed. Use \"Reset Leaderboard\" to create a new one.\n\n";
		return;
	}
	std::cout << "=========LEADERBOARD=========\nName\t\t\t" << "Score\n";
	for (int i = 0; i < 5; i++)
	{
		std::cout << vector_leaderboard[i].name << "\t\t\t" << vector_leaderboard[i].score << "\n";
	}
	std::cout << "\n";
}
bool Leaderboard::update(int score, bool mode, bool player_id)
{
	/*
	update Leaderboard with int score:
	return 1 if leaderboard.txt is updated
	return 0 if not

	mode:
	mode 0 = singleplayer (or bot)
	mode 1 = multiplayer

	player_id:
	player_id 0 = Player 1;
	palyer_id 1 = Player 2;
	*/
	if (read_error("leaderboard.txt"))
	{
		std::cout << "Leaderboard file cannot be accessed. Use \"Reset Leaderboard\" to create a new one.\n\n";
		return 0;
	}
	std::ofstream writeto("leaderboard.txt");
	bool done = 0;
	for (int i = 0; i < 5; i++)
	{
		if (!done && score > vector_leaderboard[i].score)
		{
			for (int j = 4; j > i; j--)
			{
				if (i < 4)
				{
					vector_leaderboard[j].name = vector_leaderboard[j - 1].name;
					vector_leaderboard[j].score = vector_leaderboard[j - 1].score;
				}
			}
			std::string name;
			if (mode == 0)
			{
				std::cout << "You are on the leaderboard! What is your name?: ";
			}
			else
			{
				std::cout << "Player " << player_id + 1 << ", you are on the leaderboard! Enter your name: ";
			}
			std::cin >> name;
			writeto << name << "\t" << score << "\n";
			done = 1;
		}
		else
		{
			writeto << vector_leaderboard[i].name << "\t" << vector_leaderboard[i].score << "\n";
		}
	}
	writeto.close();
	std::cout << "\n";
	if (done)
	{
		return 1;
	}
	return 0;
}
void Leaderboard::reset()
{
	if (read_error("leaderboard.txt"))
	{
		std::cout << "Leaderboard cannot be accessed. Creating a new one.\n\n";
	}
	else
	{
		std::cout << "Leaderboard reset.\n\n";
	}
	std::ofstream writeto("leaderboard.txt");
	writeto << "Bill\t250\nJohn\t200\nMaria\t150\nMartin\t100\nPhilip\t50";
	writeto.close();
}