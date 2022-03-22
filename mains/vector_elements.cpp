#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <vector>
#include <iostream>

int main ()
{
	TESTED_NAMESPACE::vector<int> myvector(10, 0);
	TESTED_NAMESPACE::vector<int>::size_type sz = myvector.size();

	for (unsigned i=0; i<sz; i++) myvector[i]=i;
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector[sz-1-i];
		myvector[sz-1-i]=myvector[i];
		myvector[i]=temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector[i];
		std::cout << '\n';

	std::cout << "----------------------------------------" << std::endl;
	myvector.push_back(78);
	myvector.push_back(16);
	TESTED_NAMESPACE::vector<int>::iterator it = myvector.begin();
	myvector.insert(it, 8);
	std::cout << "myvector.front() is now " << myvector.front() << '\n';

	std::cout << "----------------------------------------" << std::endl;
	std::cout << "myvector.back() is " << myvector.back() << '\n';
	myvector.push_back(myvector.front());
	std::cout << "myvector.back() is now " << myvector.back() << '\n';

	return 0;
}