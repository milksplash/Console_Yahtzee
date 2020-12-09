#include <iostream>
#include <fstream>
#include <ctime>
#include "Header.h"
#include "Players.h"
#include "Leaderboard.h"
#include "Options.h"
#include "Utility.h"
#include "Debug.h"

int main()
{
	srand(time(NULL));
	Leaderboard leaderboard;
	Debug debug;
	print_logo();
	leaderboard.get();

	int choice;
	do
	{
		std::cout << "<1> Play Singleplayer\t<2> Play Multiplayer\t<4> Show Leaderboard\t<5> Reset Leaderboard\t<0> Exit\n\n";
		std::cout << "Choose an option: ";
		std::cin >> choice;
		std::cout << "\n";

		int single_score = 0;
		std::vector<int> multi_scores = { 0, 0 };
		int debug_score;
		std::vector<int> debug_scores = { 0, 0 };

		switch (choice)
		{
		case 0:
			std::cout << "Goodbye...\n\n";
			system("pause");
			return 0;
		case 1:
			single_score = playsingle();
			if (leaderboard.update(single_score))
			{
				leaderboard.get();
				leaderboard.print();
			}
			system("pause");
			std::cout << "\n";
			break;
		case 2:	//Local multiplayer
			multi_scores = playmulti();
			if (leaderboard.update(std::max(multi_scores[0], multi_scores[1]), 1, (multi_scores[0] < multi_scores[1] ? 1 : 0)))
			{
				leaderboard.get();
				leaderboard.update(std::min(multi_scores[0], multi_scores[1]), 1, (multi_scores[0] < multi_scores[1] ? 0 : 1));
				leaderboard.get();
				leaderboard.print();
			}
			system("pause");
			std::cout << "\n";
			break;
		case 3:	//Vs bot
			break;
		case 4:
			leaderboard.get();
			if (!read_error("leaderboard.txt"))
			{
				leaderboard.print();
			}
			break;
		case 5:
			leaderboard.reset();
			break;
		case 99: //debug leaderboard
			std::cout << "Leaderboard debug mode 1(enter score): ";
			std::cin >> debug_score;
			if (leaderboard.update(debug_score))
			{
				leaderboard.get();
				leaderboard.print();
			}
			system("pause");
			std::cout << "\n";
			break;
		case 999: //debug multiplayer leaderboard
			std::cout << "Leaderboard debug mode 2(enter 2 scores): ";
			std::cin >> debug_scores[0] >> debug_scores[1];
			if (leaderboard.update(std::max(debug_scores[0], debug_scores[1]), 1, (debug_scores[0] < debug_scores[1] ? 1 : 0)))
			{
				leaderboard.get();
				leaderboard.update(std::min(debug_scores[0], debug_scores[1]), 1, (debug_scores[0] < debug_scores[1] ? 0 : 1));
				leaderboard.get();
				leaderboard.print();
			}
			system("pause");
			std::cout << "\n";
		case 9999: //debug singleplayer with controlled dice roll
			std::cout << "Entering debug mode...\n";
			debug.debug_play();
			system("pause");
			std::cout << "\n";
		case 99999:
			std::cout << "Entering debug mode...\n";
			debug.debug_play2();
			system("pause");
			std::cout << "\n";
		}
	} while (choice != 0);
}