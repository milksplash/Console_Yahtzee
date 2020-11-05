#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Leaderboard.h"

void Leaderboard::get()
	{
		std::ifstream readfrom("leaderboard.txt");
		if (!readfrom.is_open())
		{
			std::cout << "Leaderboard cannot be accessed.\n";
			readfrom.close();
			return;
		}
		for (int i = 0; i < 5; i++)
		{
			readfrom >> vector_leaderboard[i].name >> vector_leaderboard[i].score;
		}
		readfrom.close();
	}
void Leaderboard::print()
	{
		std::cout << "=========LEADERBOARD=========\nName\t\t\t" << "Score\n";
		for (int i = 0; i < 5; i++)
		{
			std::cout << vector_leaderboard[i].name << "\t\t\t" << vector_leaderboard[i].score << "\n";
		}
		std::cout << "\n";
	}
void Leaderboard::update(int score)
	{
		std::ofstream writeto("leaderboard.txt");
		if (!writeto.is_open())
		{
			std::cout << "Leaderboard cannot be accessed.\n";
			writeto.close();
			return;
		}
		bool done = 0;
		for (int i = 0; i < 5; i++)
		{
			if (!done && score > vector_leaderboard[i].score)
			{
				std::string name;
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
	}
void Leaderboard::reset()
{
	std::ofstream writeto("leaderboard.txt");
	if (!writeto.is_open())
	{
		std::cout << "Leaderboard cannot be accessed.\n";
		writeto.close();
		return;
	}
	writeto <<"Bill\t250\nJohn\t200\nMaria\t150\nMartin\t100\nPhilip\t50";
	writeto.close();
}