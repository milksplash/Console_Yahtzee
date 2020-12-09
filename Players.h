#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>
#include <string>
#include "Leaderboard.h"
#include "Options.h"

class Players
{
	struct Dice
	{
		int side;
		bool roll_hold;
	};
	struct Scores
	{
		int score;
		bool taken;
	};
	int score = 0;
	std::vector<Scores> scores	{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0}
	};
	std::vector<Dice> dice;
	std::vector<int> T_dice = { 0,0,0,0,0,0 };
	Options options;	//temp solution to options setting
	void update_T_dice();
	int side_total();
	void choose_combo(bool myahtzee = 0);
	void update_combo(int combo, bool myahtzee = 0);
	int get_combo_score(int combo, bool myahtzee = 0);
	void swap_dice(int die);
	void sort_dice();
	void print_dice();
	int no_rolling_dice();
	int bonus();
	int find_side_count(int ele);
	bool straight_check(int i = 1, int j = 4);
public:
	int roll_left = 3;
	void roll_dice();
	void print_scoreboard_new(bool size = 0, bool instr = 1, int score = 0);
	void print_scoreboard(int mode = 0);
	void print_scoreboard_values(int mode = 0);
	void choose_swap(bool myahtzee = 0);
	void reset_dice();
	int total_score(bool sum = 0);
	int yahtzee_check_new(bool mode = 0);
	int yahtzee_check(bool mode = 0);
	friend class Debug;
};

#endif