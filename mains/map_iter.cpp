#include <iostream>
#include "../map.hpp"
#include "../utils.hpp"
#include <map>

int main()
{
	TESTED_NAMESPACE::map<char, int> test;
	test.insert(TESTED_NAMESPACE::pair<char, int>('a', 1));
	test.insert(TESTED_NAMESPACE::pair<char, int>('b', 2));
	test.insert(TESTED_NAMESPACE::pair<char, int>('c', 3));
	test.insert(TESTED_NAMESPACE::pair<char, int>('d', 4));
	test.insert(TESTED_NAMESPACE::pair<char, int>('e', 5));
	test.insert(TESTED_NAMESPACE::pair<char, int>('f', 6));
	test.insert(TESTED_NAMESPACE::pair<char, int>('g', 7));
	test.insert(TESTED_NAMESPACE::pair<char, int>('h', 8));
	
	std::cout << "-----------------------------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int>::iterator it = test.begin();
	TESTED_NAMESPACE::map<char,int>::iterator it_bis(it);
	std::cout << (*it).first << (*it).second << std::endl;
	std::cout << (*it_bis).first << (*it_bis).second << std::endl;

	std::cout << "-----------------------------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int>::iterator ite = test.end();
	TESTED_NAMESPACE::map<char,int>::iterator ite_bis(ite);
	ite --;
	ite_bis --;
	std::cout << (*ite).first << (*ite).second << std::endl;
	std::cout << (*ite_bis).first << (*ite_bis).second << std::endl;

	std::cout << "-----------------------------------------" << std::endl;
	it++;
	std::cout << (*it).first << (*it).second << std::endl;
	++it;
	std::cout << (*it).first << (*it).second << std::endl;
	--it;
	std::cout << (*it).first << (*it).second << std::endl;
	it--;
	std::cout << (*it).first << (*it).second << std::endl;

	std::cout << "-----------------------------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int>::iterator it_rhs = test.end();
	TESTED_NAMESPACE::map<char,int>::iterator it_lhs = test.begin();
	
	std::cout << (it_rhs == it_lhs) << std::endl;
	std::cout << (it_rhs != it_lhs) << std::endl;

	std::cout << "-----------------REVERSE------------------------" << std::endl;
	TESTED_NAMESPACE::map<char, int> test_rev;
	test_rev.insert(TESTED_NAMESPACE::pair<char, int>('b', 2));
	test_rev.insert(TESTED_NAMESPACE::pair<char, int>('c', 3));
	test_rev.insert(TESTED_NAMESPACE::pair<char, int>('e', 5));
	test_rev.insert(TESTED_NAMESPACE::pair<char, int>('f', 6));
	test_rev.insert(TESTED_NAMESPACE::pair<char, int>('h', 8));
	test_rev.insert(TESTED_NAMESPACE::pair<char, int>('a', 1));
	test_rev.insert(TESTED_NAMESPACE::pair<char, int>('g', 7));
	test_rev.insert(TESTED_NAMESPACE::pair<char, int>('d', 4));

	TESTED_NAMESPACE::map<char,int>::reverse_iterator it_rev = test_rev.rbegin();
	TESTED_NAMESPACE::map<char,int>::reverse_iterator it_rev_bis(it_rev);
	std::cout << (*it_rev).first << (*it_rev).second << std::endl;
	std::cout << (*it_rev_bis).first << (*it_rev_bis).second << std::endl;
	it_rev_bis = test_rev.rend();
	it_rev_bis--;
	std::cout << (*it_rev_bis).first << (*it_rev_bis).second << std::endl;

	std::cout << "-----------------------------------------" << std::endl;
	it_rev++;
	std::cout << (*it_rev).first << (*it_rev).second << std::endl;
	++it_rev;
	std::cout << (*it_rev).first << (*it_rev).second << std::endl;
	--it_rev;
	std::cout << (*it_rev).first << (*it_rev).second << std::endl;
	it_rev--;
	std::cout << (*it_rev).first << (*it_rev).second << std::endl;

	std::cout << "-----------------------------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int>::reverse_iterator itrev_rhs = test_rev.rend();
	TESTED_NAMESPACE::map<char,int>::reverse_iterator itrev_lhs = test_rev.rbegin();
	
	std::cout << (itrev_rhs == itrev_lhs) << std::endl;
	std::cout << (itrev_rhs != itrev_lhs) << std::endl;
	return (0);
}


