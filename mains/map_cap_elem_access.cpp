#include <iostream>
#include "../map.hpp"
#include "../utils.hpp"
#include <map>

int main()
{
	std::cout << "----------------------------empty---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int> yo;

	yo['a']=10;
	yo['b']=20;
	yo['c']=30;
	while (!yo.empty())
	{
		std::cout << yo.begin()->first << " => " << yo.begin()->second << '\n';
		yo.erase(yo.begin());
	}
	
	std::cout << "----------------------------max_size---------------------" << std::endl;
	int i;
	TESTED_NAMESPACE::map<int,int> mymap;

	if (mymap.max_size()>1000)
	{
		for (i=0; i<1000; i++) mymap[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else
		std::cout << "The map could not hold 1000 elements.\n";
	std::cout << mymap.max_size() << std::endl;
	
	std::cout << "----------------------------[]---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,std::string> test;
	test['a']="an element";
	test['b']="another element";
	test['c']=test['b'];

	std::cout << "test['a'] is " << test['a'] << '\n';
	std::cout << "test['b'] is " << test['b'] << '\n';
	std::cout << "test['c'] is " << test['c'] << '\n';
	std::cout << "test['d'] is " << test['d'] << '\n';
	std::cout << "test now contains " << test.size() << " elements.\n";
}