#include <iostream>
#include "../map.hpp"
#include "../utils.hpp"
#include <map>

int main ()
{
	std::cout << "----------------------------find---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int> test_find;
	TESTED_NAMESPACE::map<char,int>::iterator it_find;

	test_find['a']=50;
	test_find['b']=100;
	test_find['c']=150;
	test_find['d']=200;

	// print content:
	std::cout << "elements in test_find:" << '\n';
	std::cout << "a => " << test_find.find('a')->second << '\n';
	std::cout << "c => " << test_find.find('c')->second << '\n';
	std::cout << "d => " << test_find.find('d')->second << '\n';

	std::cout << "----------------------------count---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int> mymap;
	char c;

	mymap ['a']=101;
	mymap ['c']=202;
	mymap ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
		else 
			std::cout << " is not an element of mymap.\n";
	}

	std::cout << "----------------------------lower bound---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int> lower_bound_test;
	TESTED_NAMESPACE::map<char,int>::iterator itlow,itup;
	TESTED_NAMESPACE::map<char,int>::iterator yolo;

	lower_bound_test['a']=20;
	lower_bound_test['b']=40;
	lower_bound_test['c']=60;
	lower_bound_test['d']=80;
	lower_bound_test['e']=100;

	for (yolo=lower_bound_test.begin(); yolo!=lower_bound_test.end(); ++yolo)
		std::cout << yolo->first << " => " << yolo->second << '\n';

	itlow=lower_bound_test.lower_bound ('b');	// itlow points to b
	itup=lower_bound_test.upper_bound ('d');	 // itup points to e (not d!)

	std::cout << "itlow : " << itlow->first << std::endl;
	std::cout << "itup : " << itup->first << std::endl;

	lower_bound_test.erase(itlow,itup);	// erases [itlow,itup)

	// // print content:
	for (yolo=lower_bound_test.begin(); yolo!=lower_bound_test.end(); ++yolo)
		std::cout << yolo->first << " => " << yolo->second << '\n';

	std::cout << "----------------------------equal range---------------------" << std::endl;

	TESTED_NAMESPACE::map<char,int> ertest;

	ertest['a']=10;
	ertest['b']=20;
	ertest['c']=30;

	TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<char,int>::iterator,TESTED_NAMESPACE::map<char,int>::iterator> ret;
	ret = ertest.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

	ret = ertest.equal_range('h');

	ret.first--;
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	ret.second--;
	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
	return 0;
}
