#include <iostream>
#include <sstream>

#include "tree.hpp"

int main()
{
	bool success = true;
	while (success) {
		std::string stroka;
		getline(std::cin, stroka);
		std::istringstream istream(stroka);
		success = D.read(istream);
	}

	std::cin.get();
    return 0;
}
