#include <iostream>
#include "../map.hpp"
#include "../utils.hpp"
#include <map>

int main ()
{
	TESTED_NAMESPACE::map<char,int> first;
	first.insert(TESTED_NAMESPACE::pair<char, int>('a', 1));
	first.insert(TESTED_NAMESPACE::pair<char, int>('b', 2));
	first.insert(TESTED_NAMESPACE::pair<char, int>('c', 3));
	first.insert(TESTED_NAMESPACE::pair<char, int>('d', 4));
	first.insert(TESTED_NAMESPACE::pair<char, int>('e', 5));
	first.insert(TESTED_NAMESPACE::pair<char, int>('f', 6));
	first.insert(TESTED_NAMESPACE::pair<char, int>('g', 7));
	first.insert(TESTED_NAMESPACE::pair<char, int>('h', 8));
	std::cout << "first size : " << first.size() << std::endl;

	TESTED_NAMESPACE::map<char, int>::iterator it;
	for(it = first.begin(); it != first.end(); ++it)
		std::cout << "test for loop : " << (*it).first << " - " << (*it).second << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	
	TESTED_NAMESPACE::map<char, int>::iterator ite = first.end();
	it = first.begin();
	ite--;
	ite--;
	ite--;
	it++;
	it++;
	TESTED_NAMESPACE::map<char,int> second(it, ite);
	for(it = second.begin(); it != second.end(); ++it)
		std::cout << "test for loop : " << (*it).first << " - " << (*it).second << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

	TESTED_NAMESPACE::map<char,int> third = second;
	for(it = third.begin(); it != third.end(); ++it)
		std::cout << "test for loop : " << (*it).first << " - " << (*it).second << std::endl;
	return 0;
}
