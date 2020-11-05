#ifndef LEADERBOARD
#define LEADERBOARD

class Leaderboard 
{
	struct Struct_leaderboard
	{
		std::string name;
		int score;
	};
	std::vector<Struct_leaderboard> vector_leaderboard { 
		{ "",0 },
		{ "",0 },
		{ "",0 },
		{ "",0 },
		{ "",0 }, 
	};
public:
	void get();
	void print();
	bool update(int score);
	void reset();
	bool read_error();
};

#endif