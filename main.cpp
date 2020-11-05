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
	do
	{
		leaderboard.get();
		int single_score = 0;

		std::cout << "1. Play Singleplayer\t4. Show Leaderboard\t5. Reset/Create Leaderboard\t0. Exit\n";
		std::cin >> choice;
		switch (choice)
		{
		case 0:	//Exit
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
			leaderboard.print();
			break;
		case 5:
			leaderboard.reset();
			break;
		case 9: //debug
			leaderboard.update(999);
		}
	} while (choice != 0);

}