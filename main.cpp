#include <iostream>
#include <fstream>
#include <ctime>
#include "Header.h"
#include "Players.h"
#include "Leaderboard.h"

int main()
{
	srand(time(NULL));
	int choice;
	Leaderboard leaderboard;
	print_logo();
	leaderboard.get();
	do
	{
		std::cout << "<1> Play Singleplayer\t<4> Show Leaderboard\t<5> Reset Leaderboard\t<0> Exit\n";
		std::cin >> choice;
		std::cout << "\n";

		int single_score = 0;

		switch (choice)
		{
		case 0:
			std::cout << "Goodbye...\n\n";
			system("pause");
			return 0;
		case 1:
			single_score = playsingle();
			leaderboard.update(single_score);
			break;
		case 2:	//Local multiplayer; should pass vector instead of int
			break;
		case 3:	//Vs bot
			break;
		case 4:
			leaderboard.get();
			if (!leaderboard.read_error())
			{
				leaderboard.print();
			}
			break;
		case 5:
			leaderboard.reset();
			break;
		case 9: //debug leaderboard
			leaderboard.update(999);
		}
	} while (choice != 0);

}