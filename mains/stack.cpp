#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <stack>
#include <iostream>

int main()
{	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~member ft~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::cout << "-------------------" << std::endl;
	TESTED_NAMESPACE::stack<int> test_int;
	test_int.push(18);
	std::cout << "empty : " << test_int.empty() << std::endl;
	test_int.push(66);
	test_int.push(90);
	std::cout << "top : " << test_int.top() << std::endl;
	std::cout << "empty : " << test_int.empty() << std::endl;
	test_int.pop();
	std::cout << "top : " << test_int.top() << std::endl;
	std::cout << "size : " << test_int.size() << std::endl;

	std::cout << "-------------------" << std::endl;
	TESTED_NAMESPACE::stack<std::string> test_string;
	test_string.push("ordinateur");
	std::cout << "empty : " << test_string.empty() << std::endl;
	test_string.push("radiateur");
	test_string.push("congelateur");
	std::cout << "top : " << test_string.top() << std::endl;
	std::cout << "empty : " << test_string.empty() << std::endl;
	test_string.pop();
	std::cout << "top : " << test_string.top() << std::endl;
	std::cout << "size : " << test_string.size() << std::endl;

	std::cout << "-------------------" << std::endl;
	TESTED_NAMESPACE::stack<float> test_float;
	test_float.push(666.666f);
	std::cout << "empty : " << test_float.empty() << std::endl;
	test_float.push(12.8f);
	test_float.push(42.6f);
	std::cout << "top : " << test_float.top() << std::endl;
	std::cout << "empty : " << test_float.empty() << std::endl;
	test_float.pop();
	std::cout << "top : " << test_float.top() << std::endl;
	std::cout << "size : " << test_float.size() << std::endl;

	// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Non-member function overloads~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::stack<int> a;
	TESTED_NAMESPACE::stack<int> b;
	a.push(12);
	a.push(3);
	b.push(12);
	b.push(3);
	if (a == b)
		std::cout << "the two stacks are equal" << std::endl;
	else
		std::cout << "the two stacks are different" << std::endl;
	
	a.pop();
	if (a == b)
		std::cout << "the two stacks are equal" << std::endl;
	else
		std::cout << "the two stacks are different" << std::endl;
	
	a.push(44);
	if (a == b)
		std::cout << "the two stacks are equal" << std::endl;
	else
		std::cout << "the two stacks are different" << std::endl;

	if (a==b) std::cout << "a and b are equal\n";
	if (a!=b) std::cout << "a and b are not equal\n";
	if (a< b) std::cout << "a is less than b\n";
	if (a> b) std::cout << "a is greater than b\n";
	if (a<=b) std::cout << "a is less than or equal to b\n";
	if (a>=b) std::cout << "a is greater than or equal to b\n";
}