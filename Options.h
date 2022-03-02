#ifndef OPTIONS
#define OPTIONS

class Options
{
	bool language;
	bool zero_confirm;
	int difficulty;
	Options()
	{
		get();
	}
	void get();
	friend class Players;
};

#endif