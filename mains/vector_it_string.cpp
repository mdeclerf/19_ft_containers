
#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <iostream>
#include <typeinfo>
#include <iostream>
#include <vector>

int main()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~VECTOR STRING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::vector<std::string> test;
	test.push_back("aa");
	test.push_back("bb");
	test.push_back("cc");
	test.push_back("dd");
	test.push_back("ee");
	test.push_back("ff");
	test.push_back("gg");
	test.push_back("hh");
	test.push_back("ii");

	TESTED_NAMESPACE::vector<std::string>::iterator it;
	TESTED_NAMESPACE::vector<std::string>::iterator ite = test.end();
	for(it = test.begin(); it != ite; ++it)
	{
		std::cout << "test for loop : " << (*it) << std::endl;
	}
	std::cout << "----------------------------------------------------------" << std::endl;
	
	it = test.begin();
	ite = test.end();
	ite--;
	std::cout << "it == ite: " << (it == ite) << std::endl;
	std::cout << "it != ite: " << (it != ite) << std::endl;
	std::cout << "it < ite: " << (it < ite) << std::endl;
	std::cout << "it > ite: " << (it > ite) << std::endl;
	std::cout << "it <= ite: " << (it <= ite) << std::endl;
	std::cout << "it >= ite: " << (it >= ite) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	it = test.begin();
	ite = test.end();
	std::cout << "test begin: " << (*it) << std::endl;
	it++;
	std::cout << "it++: " << (*it) << std::endl;
	++it;
	std::cout << "++it: " << (*it) << std::endl;
	it--;
	std::cout << "it--: " << (*it) << std::endl;
	--it;
	std::cout << "--it: " << (*it) << std::endl;
	it += 3;
	std::cout << "it += 3: " << (*it) << std::endl;
	it -= 2;
	std::cout << "it -= 2: " << (*it) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	it = test.begin() + 3;
	std::cout << "test.begin() + 3: " << (*it) << std::endl;
	ite = test.end() - 3;
	std::cout << "test.end() - 3: " << (*ite) << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	it = test.begin();
	ite = test.end();
	std::cout << "ite - it : " << ite - it << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	it = test.begin();
	std::cout << "it[4] : " << it[4] << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	it = test.begin();
	ite = test.end();
	(*it) = "yolo";
	it++;
	(*it) = "coucou";
	for(it = test.begin(); it != ite; ++it)
	{
		std::cout << "test for non constness : " << (*it) << std::endl;
	}
	
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~const_iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::vector<std::string> test_const;
	test_const.push_back("aa");
	test_const.push_back("bb");
	test_const.push_back("cc");
	test_const.push_back("dd");
	test_const.push_back("ee");
	test_const.push_back("ff");
	test_const.push_back("gg");
	test_const.push_back("hh");
	test_const.push_back("ii");

	TESTED_NAMESPACE::vector<std::string>::const_iterator it_const;
	TESTED_NAMESPACE::vector<std::string>::const_iterator ite_const = test_const.end();
	for(it_const = test_const.begin(); it_const != ite_const; ++it_const)
	{
		std::cout << "test_const for loop : " << (*it_const) << std::endl;
	}
	std::cout << "----------------------------------------------------------" << std::endl;
	
	it_const = test_const.begin();
	ite_const = test_const.end();
	ite_const--;
	std::cout << "it_const == ite_const: " << (it_const == ite_const) << std::endl;
	std::cout << "it_const != ite_const: " << (it_const != ite_const) << std::endl;
	std::cout << "it_const < ite_const: " << (it_const < ite_const) << std::endl;
	std::cout << "it_const > ite_const: " << (it_const > ite_const) << std::endl;
	std::cout << "it_const <= ite_const: " << (it_const <= ite_const) << std::endl;
	std::cout << "it_const >= ite_const: " << (it_const >= ite_const) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	it_const = test_const.begin();
	ite_const = test_const.end();
	std::cout << "test_const begin: " << (*it_const) << std::endl;
	it_const++;
	std::cout << "it_const++: " << (*it_const) << std::endl;
	++it_const;
	std::cout << "++it_const: " << (*it_const) << std::endl;
	it_const--;
	std::cout << "it_const--: " << (*it_const) << std::endl;
	--it_const;
	std::cout << "--it_const: " << (*it_const) << std::endl;
	it_const += 3;
	std::cout << "i_constt += 3: " << (*it_const) << std::endl;
	it_const -= 2;
	std::cout << "it_const -= 2: " << (*it_const) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	it_const = test_const.begin() + 3;
	std::cout << "test_const.begin() + 3: " << (*it_const) << std::endl;
	ite_const = test_const.end() - 3;
	std::cout << "test_const.end() - 3: " << (*ite_const) << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	it_const = test_const.begin();
	ite_const = test_const.end();
	std::cout << "ite_const - it : " << ite_const - it_const << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	it_const = test_const.begin();
	std::cout << "it_const[4] : " << it_const[4] << std::endl;

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~reverse_iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::vector<std::string> testreverse;
	testreverse.push_back("aa");
	testreverse.push_back("bb");
	testreverse.push_back("cc");
	testreverse.push_back("dd");
	testreverse.push_back("ee");
	testreverse.push_back("ff");
	testreverse.push_back("gg");
	testreverse.push_back("hh");
	testreverse.push_back("ii");

	TESTED_NAMESPACE::vector<std::string>::reverse_iterator rit;
	TESTED_NAMESPACE::vector<std::string>::reverse_iterator rite = testreverse.rend();
	for(rit = testreverse.rbegin(); rit != rite; ++rit)
	{
		std::cout << "test for loop : " << (*rit) << std::endl;
	}
	std::cout << "----------------------------------------------------------" << std::endl;

	rit = testreverse.rbegin();
	rite = testreverse.rend();
	rit++;
	std::cout << "rit == rite: " << (rit == rite) << std::endl;
	std::cout << "rit != rite: " << (rit != rite) << std::endl;
	std::cout << "rit < rite: " << (rit < rite) << std::endl;
	std::cout << "rit > rite: " << (rit > rite) << std::endl;
	std::cout << "rit <= rite: " << (rit <= rite) << std::endl;
	std::cout << "rit >= rite: " << (rit >= rite) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	rit = testreverse.rbegin();
	rite = testreverse.rend();
	std::cout << "test rbegin: " << (*rit) << std::endl;
	rit++;
	std::cout << "rit++: " << (*rit) << std::endl;
	++rit;
	std::cout << "++rit: " << (*rit) << std::endl;
	rit--;
	std::cout << "rit--: " << (*rit) << std::endl;
	--rit;
	std::cout << "--rit: " << (*rit) << std::endl;
	rit += 3;
	std::cout << "rit += 3: " << (*rit) << std::endl;
	rit -= 2;
	std::cout << "rit -= 2: " << (*rit) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	rit = testreverse.rbegin() + 3;
	std::cout << "testreverse.rbegin() + 3: " << (*rit) << std::endl;
	rite = testreverse.rend() - 3;
	std::cout << "testreverse.rend() - 3: " << (*rite) << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	rit = testreverse.rbegin();
	rite = testreverse.rend();
	std::cout << "rite - rit : " << rite - rit << std::endl;
	rite -= 5;
	std::cout << "rite - rit : " << rite - rit << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	rit = testreverse.rbegin();
	std::cout << "rit[4] : " << rit[4] << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	rit = testreverse.rbegin();
	rite = testreverse.rend();
	(*rit) = "yolo";
	rit++;
	(*rit) = "coucou";
	for(rit = testreverse.rbegin(); rit != rite; ++rit)
	{
		std::cout << "test for non constness : " << (*rit) << std::endl;
	}
	
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~const_reverse_iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::vector<std::string> testconstreverse;
	testconstreverse.push_back("aa");
	testconstreverse.push_back("bb");
	testconstreverse.push_back("cc");
	testconstreverse.push_back("dd");
	testconstreverse.push_back("ee");
	testconstreverse.push_back("ff");
	testconstreverse.push_back("gg");
	testconstreverse.push_back("hh");
	testconstreverse.push_back("ii");

	TESTED_NAMESPACE::vector<std::string>::const_reverse_iterator crit;
	TESTED_NAMESPACE::vector<std::string>::const_reverse_iterator crite = testconstreverse.rend();
	for(crit = testconstreverse.rbegin(); crit != crite; ++crit)
	{
		std::cout << "test for loop : " << (*crit) << std::endl;
	}
	std::cout << "----------------------------------------------------------" << std::endl;

	crit = testconstreverse.rbegin();
	crite = testconstreverse.rend();
	crit++;
	std::cout << "crit == crite: " << (crit == crite) << std::endl;
	std::cout << "crit != crite: " << (crit != crite) << std::endl;
	std::cout << "crit < crite: " << (crit < crite) << std::endl;
	std::cout << "crit > crite: " << (crit > crite) << std::endl;
	std::cout << "crit <= crite: " << (crit <= crite) << std::endl;
	std::cout << "crit >= crite: " << (crit >= crite) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	crit = testconstreverse.rbegin();
	crite = testconstreverse.rend();
	std::cout << "test rbegin: " << (*crit) << std::endl;
	crit++;
	std::cout << "crit++: " << (*crit) << std::endl;
	++crit;
	std::cout << "++crit: " << (*crit) << std::endl;
	crit--;
	std::cout << "crit--: " << (*crit) << std::endl;
	--crit;
	std::cout << "--crit: " << (*crit) << std::endl;
	crit += 3;
	std::cout << "crit += 3: " << (*crit) << std::endl;
	crit -= 2;
	std::cout << "crit -= 2: " << (*crit) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	crit = testconstreverse.rbegin() + 3;
	std::cout << "testconstreverse.rbegin() + 3: " << (*crit) << std::endl;
	crite = testconstreverse.rend() - 3;
	std::cout << "testconstreverse.rend() - 3: " << (*crite) << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	crit = testconstreverse.rbegin();
	crite = testconstreverse.rend();
	std::cout << "crite - crit : " << crite - crit << std::endl;
	crite -= 5;
	std::cout << "crite - crit : " << crite - crit << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	crit = testconstreverse.rbegin();
	std::cout << "crit[4] : " << crit[4] << std::endl;

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}
