#if STL

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#define SEED 67
#define COUNT 100000

int main()
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~STL~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	srand(SEED);
	std::map<int, int> map_int;
	for (int i = 0; i < 1000; ++i)
	{
		std::pair<int,int> value(rand(), rand() % 100);
		map_int.insert(value);
	}
	int sum = 0;
	for(std::map<int, int>::iterator it = map_int.begin(); it != map_int.end(); ++it)
	{
		if (it->first % 10)
			sum += it->second;
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	std::cout << "---------------------------------------------" << std::endl;
	std::vector<int> vector_int;
	for (int i = 0; i < COUNT; i++)
	{
		vector_int.push_back(rand());
	}
	for (int i = 0; i < COUNT; i++)
	{
		if (vector_int[i] % 1)
			vector_int[i] = i + 1;
	}
	for (int i = 0; i < COUNT; i++)
	{
		if (vector_int[i] % 1)
			vector_int[i] = i + 1;
	}

	std::vector<int> vector_int_swap(COUNT, 0);
	vector_int_swap.swap(vector_int);

	size_t sum_vect = 0;
	for(std::vector<int>::iterator it = vector_int_swap.begin(); it != vector_int_swap.end(); ++it)
		sum_vect+=(*it);
	size_t sum_bis = 0;
	for(std::vector<int>::iterator it = vector_int.begin(); it != vector_int.end(); ++it)
		sum+=(*it);
	std::cout << "should be constant with the same seed: " << sum_vect << std::endl;
	std::cout << "should be constant with the same seed: " << sum_bis << std::endl;

	std::cout << "---------------------------------------------" << std::endl;
	std::stack<int> stack_int;
	for (int i = 0; i < COUNT; ++i)
		stack_int.push(rand());
	for (int i = 0; i < COUNT; ++i)
	{
		if (i % 1)
			stack_int.pop();
	}
}

#else

#include "map.hpp"
#include "utils.hpp"
#include "stack.hpp"
#include "iterator_vector.hpp"
#include "vector.hpp"
#define SEED 67
#define COUNT 100000

int main()
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~FT~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	srand(SEED);
	ft::map<int, int> map_int;
	for (int i = 0; i < 1000; ++i)
	{
		ft::pair<int,int> value(rand(), rand() % 100);
		map_int.insert(value);
	}
	int sum = 0;
	for(ft::map<int, int>::iterator it = map_int.begin(); it != map_int.end(); ++it)
	{
		if (it->first % 10)
			sum += it->second;
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	std::cout << "---------------------------------------------" << std::endl;
	ft::vector<int> vector_int;
	for (int i = 0; i < COUNT; i++)
	{
		vector_int.push_back(rand());
	}
	for (int i = 0; i < COUNT; i++)
	{
		if (vector_int[i] % 1)
			vector_int[i] = i + 1;
	}
	for (int i = 0; i < COUNT; i++)
	{
		if (vector_int[i] % 1)
			vector_int[i] = i + 1;
	}

	ft::vector<int> vector_int_swap(COUNT, 0);
	vector_int_swap.swap(vector_int);

	size_t sum_vect = 0;
	for(ft::vector<int>::iterator it = vector_int_swap.begin(); it != vector_int_swap.end(); ++it)
		sum_vect+=(*it);
	size_t sum_bis = 0;
	for(ft::vector<int>::iterator it = vector_int.begin(); it != vector_int.end(); ++it)
		sum+=(*it);
	std::cout << "should be constant with the same seed: " << sum_vect << std::endl;
	std::cout << "should be constant with the same seed: " << sum_bis << std::endl;

	std::cout << "---------------------------------------------" << std::endl;
	ft::stack<int> stack_int;
	for (int i = 0; i < COUNT; ++i)
		stack_int.push(rand());
	for (int i = 0; i < COUNT; ++i)
	{
		if (i % 1)
			stack_int.pop();
	}
}

#endif
