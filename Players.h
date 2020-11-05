#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>
#include <string>
#include "Header.h"
#include "Leaderboard.h"

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
	void update_T_dice();
	int side_total();
	void choose_combo();
	void update_combo(int combo);
	int get_combo_score(int combo);
	void get_scoreboard_values();
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
	void print_scoreboard();
	void choose_swap();
	void reset_dice();
	int total_score(bool sum = 0);
	friend class Debug;
	friend bool Leaderboard::update(int score);
};

#endif