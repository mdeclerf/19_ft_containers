#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <iostream>
#include <vector>

int main ()
{
	TESTED_NAMESPACE::vector<int> foo (3,100);	// three ints with a value of 100
	TESTED_NAMESPACE::vector<int> bar (5,200);	// two ints with a value of 200

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	foo.swap(bar);

	std::cout << "foo contains:";
	for (TESTED_NAMESPACE::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
	std::cout << ' ' << *it;
		std::cout << '\n';

	std::cout << "bar contains:";
	for (TESTED_NAMESPACE::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
	std::cout << ' ' << *it;
		std::cout << '\n';

	return 0;
}