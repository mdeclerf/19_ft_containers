#include <iostream>
#include "../map.hpp"
#include "../utils.hpp"
#include <map>

int main ()
{
	std::cout << "----------------------------INSERT---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( TESTED_NAMESPACE::pair<char,int>('a',100) );
	mymap.insert ( TESTED_NAMESPACE::pair<char,int>('z',200) );

	TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( TESTED_NAMESPACE::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	TESTED_NAMESPACE::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, TESTED_NAMESPACE::pair<char,int>('b',300)); 	// max efficiency inserting
	mymap.insert (it, TESTED_NAMESPACE::pair<char,int>('c',400)); 	// no max efficiency inserting

	// third insert function version (range insertion):
	TESTED_NAMESPACE::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size : " << mymap.size() << std::endl;

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size : " << anothermap.size() << std::endl;

	std::cout << "----------------------------swap---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (TESTED_NAMESPACE::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (TESTED_NAMESPACE::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "----------------------------delete node---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int> maap;
	TESTED_NAMESPACE::map<char,int>::iterator itend;

	maap.insert ( TESTED_NAMESPACE::pair<char,int>('a',100) );
	maap.insert ( TESTED_NAMESPACE::pair<char,int>('b',200) );
	maap.insert ( TESTED_NAMESPACE::pair<char,int>('c',300) );
	maap.insert ( TESTED_NAMESPACE::pair<char,int>('d',400) );
	maap.insert ( TESTED_NAMESPACE::pair<char,int>('e',500) );
	maap.insert ( TESTED_NAMESPACE::pair<char,int>('f',600) );
	maap.insert ( TESTED_NAMESPACE::pair<char,int>('g',600) );
	maap.insert ( TESTED_NAMESPACE::pair<char,int>('h',600) );
	maap.insert ( TESTED_NAMESPACE::pair<char,int>('i',600) );

	std::cout << "contents before deletion: " << std::endl;
	for (it=maap.begin(); it!=maap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	maap.erase('a');
	maap.erase('b');

	std::cout << "contents after deletion: " << std::endl;
	for (it=maap.begin(); it!=maap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	it = maap.begin();
	maap.erase(it);
	it = maap.end();
	it--;
	
	maap.erase(it);
	std::cout << "contents after deletion: " << std::endl;
	for (it=maap.begin(); it!=maap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	
	it = maap.begin();
	itend = maap.end();
	maap.erase(it, itend);

	std::cout << "contents after deletion: " << std::endl;
	for (it=maap.begin(); it!=maap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "----------------------------clear---------------------" << std::endl;
	TESTED_NAMESPACE::map<char,int> yolo;

	yolo['x']=100;
	yolo['y']=200;
	yolo['z']=300;

	std::cout << "yolo contains:\n";
	for (it=yolo.begin(); it!=yolo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "yolo now contains " << yolo.size() << " elements.\n";

	yolo.clear();
	std::cout << "yolo now contains " << yolo.size() << " elements.\n";
	yolo['a']=1101;
	yolo['b']=2202;

	std::cout << "yolo contains:\n";
	for (it=yolo.begin(); it!=yolo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "yolo now contains " << yolo.size() << " elements.\n";

	return 0;
}

