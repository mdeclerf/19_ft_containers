#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <vector>
#include <iostream>

int main()
{
	TESTED_NAMESPACE::vector<int> test(4,100);
	std::cout << "capacity fill constructor " << test.capacity() << std::endl;
	std::cout << "size fill constructor " << test.size() << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator it;
	TESTED_NAMESPACE::vector<int>::iterator ite = test.end();
	for(it = test.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;
	
	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> second (test.begin(),test.end());
	std::cout << "capacity range constructor " << second.capacity() << std::endl;
	std::cout << "size range constructor " << second.size() << std::endl;
	ite = second.end();
	for(it = second.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> third (second);
	std::cout << "capacity range constructor " << third.capacity() << std::endl;
	std::cout << "size range constructor " << third.size() << std::endl;
	ite = third.end();
	for(it = third.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> test_pb;
	test_pb.push_back(2);
	std::cout << "capacity " << test_pb.capacity() << std::endl;
	std::cout << "size " << test_pb.size() << std::endl;
	test_pb.push_back(3);
	std::cout << "capacity " << test_pb.capacity() << std::endl;
	std::cout << "size " << test_pb.size() << std::endl;
}