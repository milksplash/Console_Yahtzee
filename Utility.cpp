#include <iostream>
#include <fstream>

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

bool read_error(std::string filename)
{
	std::ifstream readfrom(filename);
	if (!readfrom.is_open())
	{
		readfrom.close();
		return 1;
	}
	readfrom.close();
	return 0;
}