#include "../map.hpp"
#include "../utils.hpp"
#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#define SEED 67

int main()
{
	srand(SEED);
	std::cout << "---------------------------------------------" << std::endl;
	TESTED_NAMESPACE::map<int, int> map_int;
	for (int i = 0; i < 1000; ++i)
	{
		TESTED_NAMESPACE::pair<int,int> value(rand(), rand() % 100);
		std::cout << value.first << value.second << std::endl;
		map_int.insert(value);
	}
	int sum = 0;
	for(TESTED_NAMESPACE::map<int, int>::iterator it = map_int.begin(); it != map_int.end(); ++it)
	{
		std::cout << it->first << std::endl;
		if (it->first % 10)
			sum += it->second;
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;
}
