#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <vector>
#include <iostream>

int main()
{
	TESTED_NAMESPACE::vector<int> test(10,100);
	std::cout << "capacity fill constructor " << test.capacity() << std::endl;
	std::cout << "size fill constructor " << test.size() << std::endl;
	std::cout << "max size : " << test.max_size() << std::endl;
	
	std::cout << "-------------------------------------------" << std::endl;
	test.resize(5, 0);
	std::cout << "resize smaller capacity " << test.capacity() << std::endl;
	std::cout << "resize smaller size " << test.size() << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator it;
	TESTED_NAMESPACE::vector<int>::iterator ite = test.end();
	for(it = test.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;
	test.resize(7, 666);
	std::cout << "resize bigger size " << test.size() << std::endl;
	if (test.size() >= test.capacity())
		std::cout << "container has enough storage" << std::endl;
	ite = test.end();
	for(it = test.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;
	test.resize(12, 8);
	std::cout << "resize bigger size " << test.size() << std::endl;
	if (test.size() >= test.capacity())
		std::cout << "container has enough storage" << std::endl;
	ite = test.end();
	for(it = test.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;

	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "is test empty ? " << test.empty() << std::endl;
	TESTED_NAMESPACE::vector<int> testb;
	std::cout << "is testb empty ? " << testb.empty() << std::endl;

	std::cout << "-------------------------------------------" << std::endl;
	testb.reserve(20);
	std::cout << "testb capacity " << testb.capacity() << std::endl;
	testb.reserve(10);
	std::cout << "testb capacity " << testb.capacity() << std::endl;
}