#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include "Header.h"
#include "Players.h"
#include "Options.h"

//Private
void Players::update_T_dice()
{
	int temp = 0;
	for (int i = 0; i < 6; i++)
	{
		temp = 0;
		for (int j = 0; j < dice.size(); j++)
		{
			if (dice[j].side == (i + 1))
			{
				temp++;
			}
		}
		T_dice[i] = temp;
	}
}
int Players::side_total()
{
	int t = 0;
	for (int i = 0; i < dice.size(); i++)
	{
		t += dice[i].side;
	}
	return t;
}
void Players::update_combo(int combo, bool myahtzee)
{
	int combo_score = get_combo_score(combo, myahtzee);
	if (!scores[combo].taken)
	{
		if (combo_score == 0 && options.zero_confirm == 1)
		{
			std::cout << "This combination will yield you 0 score, proceed? (1/0): ";
			bool proceed;
			std::cin >> proceed;
			std::cout << "\n";
			if (proceed)
			{
				scores[combo].taken = 1;
				scores[combo].score = combo_score;
				roll_left = 0;
			}
			else
			{
				choose_combo(myahtzee);
			}
		}
		else
		{
			scores[combo].taken = 1;
			scores[combo].score = combo_score;
			roll_left = 0;
		}
	}
	else
	{
		std::cout << "The combination was already chosen.\n\n";
		choose_combo(myahtzee);
	}
}
void Players::choose_combo(bool myahtzee)
{
	int choice;
	std::cout << "Choose a combination: ";
	std::cin >> choice;
	if (choice > 14)
	{
		choose_combo(myahtzee);
		return;
	}
	std::cout << "\n";
	switch (choice)
	{
	case 0:
		choose_swap();
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		update_combo(choice - 1, myahtzee);
		break;
	case 14:
		if (roll_left == 0)
		{
			std::cout << "You have no roll left this round! You must choose a combination.\n\n";
			choose_combo(myahtzee);
		}
		break;
	}
}
int Players::get_combo_score(int combo, bool myahtzee)
{
//myahtzee 1 = multiple yahtzee superset mode
	if (combo < 6)
	{
		int no_count = 0;
		for (int i = 0; i < 5; i++)
		{
			if (dice[i].side == combo + 1)
			{
				no_count += combo + 1;
			}
		}
		return no_count;
	}
	switch (combo + 1)
	{
	case 7:		//Three of a kind
		if (find_side_count(3) == 1)
		{
			return side_total();
		}
		return 0;
	case 8:		//Four of a kind
		if (find_side_count(4) == 1)
		{
			return side_total();
		}
		return 0;
	case 9:		//Full House
		if ((find_side_count(3) == 1 && find_side_count(2) == 2) || myahtzee == 1)
		{
			return 25;
		}
		return 0;
	case 10:	//Small Straight
		for (int i = 1; i < 4; i++)
		{
			if (straight_check(i, i + 3))
			{
				return 30;
			}
		}
		if (myahtzee == 1)
		{
			return 30;
		}
		return 0;
	case 11:	//Large Straight
		for (int i = 1; i < 3; i++)
		{
			if (straight_check(i, i + 4))
			{
				return 40;
			}
		}
		if (myahtzee == 1)
		{
			return 40;
		}
		return 0;
	case 12:	//Chance
	{
		return side_total();
	}
	case 13:	//Yahtzee
		if (find_side_count(5) == 1)
		{
			return 50;
		}
		return 0;
	}
	return 0;
}
void Players::swap_dice(int die)
{
	// if total number of dice holding is 4 and user is trying to hold another die, return
	if (no_rolling_dice() == 1 && dice[die].roll_hold == 0)
	{
		std::cout << "You cannot hold more than 4 dice at once!\n\n";
		return;
	}
	dice[die].roll_hold = !dice[die].roll_hold;
	sort_dice();
	print_dice();
	//debug_print_player_dice(dice);
}
void Players::sort_dice()
{
	std::sort(dice.begin(), dice.end(), [](const auto& i, const auto& j) {return i.roll_hold < j.roll_hold; });
	std::sort(dice.begin(), dice.begin() + no_rolling_dice(), [](const auto& i, const auto& j) {return i.side < j.side; });
	std::sort(dice.begin() + no_rolling_dice(), dice.end(), [](const auto& i, const auto& j) {return i.side < j.side; });
}
void Players::print_dice()
{
	int nrd = no_rolling_dice();
	std::cout << "You rolled:\n<1>\t<2>\t<3>\t<4>\t<5>\n";
	for (int i = 0; i < dice.size(); i++)
	{
		if (i == 0 && nrd != 1)
		{
			std::cout << "(" << dice[i].side << "\t";
		}
		else if (i == 0 && nrd == 1)
		{
			std::cout << "(" << dice[i].side << ")\t";
		}
		else if (dice[i].roll_hold == 0 && (i + 1) == nrd)
		{
			std::cout << " " << dice[i].side << ")\t";
		}
		else
		{
			std::cout << " " << dice[i].side << "\t";
		}
	}
	std::cout << "\n\n";
}
int Players::no_rolling_dice()
{
	int n = 0;
	for (int i = 0; i < dice.size(); i++)
	{
		if (dice[i].roll_hold == 0)
		{
			n++;
		}
	}
	return n;
}
int Players::bonus()
{
	if (total_score(1) > 63)
	{
		return 35;
	}
	return 0;
}
int Players::find_side_count(int x)
{
	//find how many sides appeared at least x time(s)
	int count = 0;
	for (int i = x; i < 6; i++)
	{
		count += std::count(T_dice.begin(), T_dice.end(), i);
	}
	return count;
}
bool Players::straight_check(int i,int j)
{
	if (i < j && T_dice[i - 1] > 0)
	{
		return straight_check(i + 1, j);
	}
	else if (T_dice[i - 1] == 0)
	{
		return 0;
	}
	return 1;
}

//Public
void Players::roll_dice()
{
	int no_dice = no_rolling_dice();

	for (int i = 0; i < no_dice; i++)
	{
		dice[i].side = rand() % 6 + 1;
	}

	sort_dice();
	print_dice();
	update_T_dice();

	roll_left--;

	std::cout << "You have " << roll_left << " roll(s) left.\n\n";

}

void Players::print_scoreboard_new(bool size, bool instr, int score)
{
	/*
	scoreboard size:
	0 = 1 row of scores, complete for singleplayer (default)
	1 = 2 rows of scores, not complete and ready to connect function extended_scoreboard
	display numeral instruction? (e.g. <1> for Ones)
	0 = do not display instruction
	1 = do display instruction (default)
	what potential score should be displayed? (only in effect when size = 0)
	0 = display potential score (default)
	1 = do not display potential score
	2 = multiple yahtzee superset mode
	*/
	if (instr == 1)
	{
		std::cout << "\t<1>\t<2>\t<3>\t<4>\t<5>\t<6>\t\t\t<7>\t<8>\t<9>\t<10>\t<11>\t<12>\t<13>\n";
	}
	std::cout << "\tOnes\tTwos\tThrees\tFours\tFives\tSixes\tSum\tBonus\tToak\tFoak\tFh\tSs\tLs\tC.\tY.\tTotal\n";
	std::cout << "========================================================================================================================================\n";
	if (size == 0)
	{
		std::cout << "You\t";
		print_scoreboard_values(score);
		std::cout << total_score();
		if (instr == 1)
		{
			std::cout << "\n\n<0>: toggle between selecting die and choosing combination\n<14>: roll die(s)";
		}
		std::cout << "\n\n";
	}
}
void Players::print_scoreboard(int mode)
{
	/*
	0 = default for singleplayer
	1 = multiplayer/bot
	2 = do not display instruction
	3 = multiple yahtzee superset mode
	*/
	if (mode != 2)
	{
		std::cout << "\t<1>\t<2>\t<3>\t<4>\t<5>\t<6>\t\t\t<7>\t<8>\t<9>\t<10>\t<11>\t<12>\t<13>\n";
	}
	std::cout << "\tOnes\tTwos\tThrees\tFours\tFives\tSixes\tSum\tBonus\tToak\tFoak\tFh\tSs\tLs\tC.\tY.\tTotal\n";
	std::cout << "========================================================================================================================================\n";
	if (mode == 0)
	{
		std::cout << "You\t";
		print_scoreboard_values();
		std::cout << total_score();
		std::cout << "\n\n<0>: toggle between selecting die and choosing combination\n<14>: roll die(s)\n\n";
	}
	if (mode == 2)
	{
		std::cout << "You\t";
		print_scoreboard_values(1);
		std::cout << total_score() << "\n\n";
	}
	if (mode == 3)
	{
		std::cout << "You\t";
		print_scoreboard_values(2);
		std::cout << total_score();
		std::cout << "\n\n<0>: toggle between selecting die and choosing combination\n<14>: roll die(s)\n\n";
	}
}

void Players::print_scoreboard_values(int mode)
{
	/*
	mode 0: display potential scores (default)
	mode 1: do not display potential scores
	mode 2: multiple yahtzee superset mode
	!! total_score function is used in bonus function
	!! cannot be broken down
	*/
	int sum = total_score(1);
	int b = bonus();
	for (int i = 0; i < 13; i++)
	{
		if (scores[i].taken)
		{
			std::cout << scores[i].score;
		}
		else
		{
			switch (mode)
			{
			case 0:
				std::cout << "(" << get_combo_score(i) << ")";
				break;
			case 2:
				std::cout << "(" << get_combo_score(i, 1) << ")";
				break;
			}
		}
		if (i == 5) //Add sum score after the Sixes score
		{
			std::cout << "\t" << sum << "\t" << b;
		}
		std::cout << "\t";
	}
}
void Players::choose_swap(bool myahtzee)
{
	if (roll_left == 0)
	{
		choose_combo(myahtzee);
		return;
	}
	std::cout << "Choose a die to hold/free: ";
	int die;
	std::cin >> die;
	std::cout << "\n";
	if (die == 0)
	{
		choose_combo(myahtzee);
		return;
	}
	if (die == 14)
	{
		if (roll_left == 0)
		{
			std::cout << "You have no roll left this round! You must choose a combination.\n\n";
			choose_combo(myahtzee);
			return;
		}
		return;
	}
	if (die > 5)
	{
		choose_swap(myahtzee);
		return;
	}
	swap_dice(die - 1);
	choose_swap(myahtzee);
}
void Players::reset_dice()
{
	dice =
	{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0}
	};
}
int	Players::total_score(bool sum)
{
	score = 0;
	for (int i = 0; i < 6; i++)
	{
		score += scores[i].score;
	}
	if (sum)
	{
		return score;
	}
	if (score > 62)
	{
		score += 35;
	}
	
	for (int i = 6; i < 13; i++)
	{
		score += scores[i].score;
	}
	return score;
}

int Players::yahtzee_check_new(bool mode)
{
	/*
	mode 0: singleplayer (default)
	mode 1: multiplayer
	return 11: need extended_scoreboard(
	return 12: need extended_scoreboard(
	*/
	if (find_side_count(5) > 0)
	{
		std::cout << "Yahtzee!\n\n";
		if (scores[12].taken == 1)
		{
			std::cout << "You have rolled more than one Yahtzee!\nYou have earned an extra 100 scores.\n\n";
			scores[12].score += 100;
			int p = std::find(T_dice.begin(), T_dice.end(), 5) - T_dice.begin();
			if (scores[p].taken == 0)
			{
				std::string N;
				switch (p)
				{
				case 0:
					N = "Ones";
					break;
				case 1:
					N = "Twos";
					break;
				case 2:
					N = "Threes";
					break;
				case 3:
					N = "Fours";
					break;
				case 4:
					N = "Fives";
					break;
				case 5:
					N = "Sixes";
					break;
				}
				std::cout << N << " has not been taken yet. Category " << N << " must be and has been taken for you.\n\n";
				scores[p].score = get_combo_score(p);
				scores[p].taken = 1;
				print_scoreboard_new(mode, 0, 1);
				roll_left = 0;
				if (mode == 1)
				{
					return 11;
				}
				return 1;
			}
			else
			{
				std::cout << "You can also select any category that is not filled yet.\n\n";
				print_scoreboard_new(mode, 1, 2);
				if (mode == 1)
				{
					return 21;
				}
				return 2;
			}
		}
	}
	return 0;
}
int Players::yahtzee_check(bool mode)
{
	/*
	mode 0: singleplayer
	mode 1: multiplayer
	return 0: there is no multiple yahtzee
	return 1: there is a multiple yahtzee, corresponding upper category not filled
	return 2: there is a multiple yahtzee, corresponding upper category filled
	*/
	if (find_side_count(5) > 0)
	{
		std::cout << "Yahtzee!\n\n";
		if (scores[12].taken == 1)
		{
			std::cout << "You have rolled more than one Yahtzee!\nYou have earned an extra 100 scores.\n\n";
			scores[12].score += 100;
			int p = std::find(T_dice.begin(), T_dice.end(), 5) - T_dice.begin();
			if (scores[p].taken == 0)
			{
				std::string N;
				switch (p)
				{
				case 0:
					N = "Ones";
					break;
				case 1:
					N = "Twos";
					break;
				case 2:
					N = "Threes";
					break;
				case 3:
					N = "Fours";
					break;
				case 4:
					N = "Fives";
					break;
				case 5:
					N = "Sixes";
					break;
				}
				std::cout << N << " has not been taken yet. Category " << N << " must be and has been taken for you.\n\n";
				scores[p].score = get_combo_score(p);
				scores[p].taken = 1;
				print_scoreboard(2);
				roll_left = 0;
				system("pause");
				return 1;
			}
			else
			{
				std::cout << "You can also select any category that is not filled yet.\n\n";
				print_scoreboard(3);
				choose_combo(1);
				return 2;
			}
		}
	}
	return 0;
}