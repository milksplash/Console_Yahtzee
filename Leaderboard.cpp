#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Leaderboard.h"

void Leaderboard::get()
{
	if (read_error())
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
	if (read_error())
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
bool Leaderboard::update(int score)
{
	//update Leaderboard with in score; 
	//return 1 if leaderboard.txt is updated
	//return 0 if not
	if (read_error())
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
	if (done)
	{
		return 1;
	}
	return 0;
}
void Leaderboard::reset()
{
	if (read_error())
	{
		std::cout << "Leaderboard cannot be accessed. Creating a new one.\n\n";
	}
	std::ofstream writeto("leaderboard.txt");
	writeto <<"Bill\t250\nJohn\t200\nMaria\t150\nMartin\t100\nPhilip\t50";
	writeto.close();
}
bool Leaderboard::read_error()
{
	std::ifstream readfrom("leaderboard.txt");
	if (!readfrom.is_open())
	{
		readfrom.close();
		return 1;
	}
	readfrom.close();
	return 0;
}