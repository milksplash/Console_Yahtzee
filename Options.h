#ifndef OPTIONS
#define OPTIONS

class Options
{
	bool language;
	bool zero_confirm;
	int difficulty;
	Options()
	{
		language = 1;
		zero_confirm = 1;
		difficulty = 1;
	}
	void get();
	void update();
	friend class Players;
};

#endif