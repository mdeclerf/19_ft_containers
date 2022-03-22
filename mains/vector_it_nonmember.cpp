#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <iostream>
#include <typeinfo>
#include <iostream>
#include <vector>

int main()
{
	std::cout << "--------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> myvector_a;
	for (int i=0; i<10; i++) myvector_a.push_back(i);

	TESTED_NAMESPACE::vector<int>::reverse_iterator from,until;

	from = myvector_a.rbegin();
	until = myvector_a.rend();

	std::cout << "myvector_a has " << (until-from) << " elements.\n";

	std::cout << "--------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> myvector_b;
	for (int i=0; i<10; i++) myvector_b.push_back(i);

	TESTED_NAMESPACE::vector<int>::iterator start,end;

	start = myvector_b.begin();
	end = myvector_b.end();

	std::cout << "myvector_b has " << (end-start) << " elements.\n";

	std::cout << "--------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> myvector_c;
	for (int i=0; i<10; i++) myvector_c.push_back(i);	// myvector_c: 0 1 2 3 4 5 6 7 8 9

	TESTED_NAMESPACE::vector<int>::reverse_iterator rev_it;

	rev_it = 3 + myvector_c.rbegin();

	std::cout << "rev_it: " << *rev_it << '\n';

	std::cout << "--------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> myvector_d;
	for (int i=0; i<10; i++) myvector_d.push_back(i);	// myvector_d: 0 1 2 3 4 5 6 7 8 9

	TESTED_NAMESPACE::vector<int>::iterator it;

	it = 3 + myvector_d.begin();

	std::cout << "it: " << *it << '\n';

	return 0;
}