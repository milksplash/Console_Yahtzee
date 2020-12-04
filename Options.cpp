#include <iostream>
#include <fstream>
#include "Options.h"
#include "Utility.h"

void Options::get()
{
	if (read_error("config.txt"))
	{
		std::ofstream writeto("config.txt");
		writeto << "1\t1\t1";
		writeto.close();
	}
	std::ifstream readfrom("config.txt");
	readfrom >> language;
	readfrom >> zero_confirm;
	readfrom >> difficulty;
	readfrom.close();
}