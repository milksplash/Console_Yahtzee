#include <iostream>
#include "Header.h"
#include "Players.h"

void print_logo()
{
	std::cout << R"(
          _______          _________ _______  _______  _______ 
|\     /|(  ___  )|\     /|\__   __// ___   )(  ____ \(  ____ \
( \   / )| (   ) || )   ( |   ) (   \/   )  || (    \/| (    \/
 \ (_) / | (___) || (___) |   | |       /   )| (__    | (__    
  \   /  |  ___  ||  ___  |   | |      /   / |  __)   |  __)   
   ) (   | (   ) || (   ) |   | |     /   /  | (      | (      
   | |   | )   ( || )   ( |   | |    /   (_/\| (____/\| (____/\
   \_/   |/     \||/     \|   )_(   (_______/(_______/(_______/
                                                               )" << "\n\n";
}

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
	system("pause");
	std::cout << "\n";
	return score;
} 