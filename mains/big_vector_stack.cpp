#include "../map.hpp"
#include "../utils.hpp"
#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <stack>

#define COUNT 100000
#define SEED 45

int main()
{
	srand(SEED);
	std::cout << "---------------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> vector_int;
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

	TESTED_NAMESPACE::vector<int> vector_int_swap(COUNT, 0);
	vector_int_swap.swap(vector_int);

	for(TESTED_NAMESPACE::vector<int>::iterator it = vector_int_swap.begin(); it != vector_int_swap.end(); ++it)
		std::cout << (*it) << std::endl;
	for(TESTED_NAMESPACE::vector<int>::iterator it = vector_int.begin(); it != vector_int.end(); ++it)
		std::cout << (*it) << std::endl;

	std::cout << "---------------------------------------------" << std::endl;
	TESTED_NAMESPACE::stack<int> stack_int;
	for (int i = 0; i < COUNT; ++i)
	{
		stack_int.push(rand());
		std::cout << stack_int.top() << std::endl;
	}
	for (int i = 0; i < COUNT; ++i)
	{
		if (i % 1)
			stack_int.pop();
	}
}
