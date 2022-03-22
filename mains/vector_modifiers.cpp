#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <iostream>
#include <iostream>
#include <vector>

int main()
{
	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> test_pb;
	test_pb.push_back(2);
	std::cout << "capacity " << test_pb.capacity() << std::endl;
	std::cout << "size " << test_pb.size() << std::endl;
	test_pb.push_back(3);
	std::cout << "capacity " << test_pb.capacity() << std::endl;
	std::cout << "size " << test_pb.size() << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	test_pb.assign(10,666);
	std::cout << "capacity " << test_pb.capacity() << std::endl;
	std::cout << "size " << test_pb.size() << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator it;
	TESTED_NAMESPACE::vector<int>::iterator ite = test_pb.end();
	for(it = test_pb.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	test_pb.assign(5,8);
	std::cout << "capacity " << test_pb.capacity() << std::endl;
	std::cout << "size " << test_pb.size() << std::endl;
	ite = test_pb.end();
	for(it = test_pb.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> shift(4, 100);
	TESTED_NAMESPACE::vector<int>::iterator itb = shift.begin();
	TESTED_NAMESPACE::vector<int>::iterator iteb = shift.end();
	test_pb.assign(itb, iteb);
	ite = test_pb.end();
	for(it = test_pb.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	test_pb.pop_back();
	ite = test_pb.end();
	for(it = test_pb.begin(); it != ite; ++it)
		std::cout << (*it) << std::endl;
	std::cout << "capacity " << test_pb.capacity() << std::endl;
	std::cout << "size " << test_pb.size() << std::endl;

	TESTED_NAMESPACE::vector<int> yolo;
	std::cout << "capacity " << yolo.capacity() << std::endl;
	std::cout << "size " << yolo.size() << std::endl;
	yolo.pop_back();
	std::cout << "capacity " << yolo.capacity() << std::endl;
	std::cout << "size " << yolo.size() << std::endl;
	yolo.pop_back();
	std::cout << "capacity " << yolo.capacity() << std::endl;
	std::cout << "size " << yolo.size() << std::endl;
	std::cout << "max size " << yolo.max_size() << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> myvector(3,100);
	std::cout << "before capacity " << myvector.capacity() << std::endl;
	std::cout << "before size " << myvector.size() << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator myiter = myvector.begin();
	myiter++;
	TESTED_NAMESPACE::vector<int>::iterator ret = myvector.insert (myiter,300);
	std::cout << "ret : " << (*ret) << std::endl;
	std::cout << "after capacity " << myvector.capacity() << std::endl;
	std::cout << "after size " << myvector.size() << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator verif;
	TESTED_NAMESPACE::vector<int>::iterator verifend = myvector.end();
	for(verif = myvector.begin(); verif != verifend; ++verif)
	{
		std::cout << (*verif) << std::endl;
	}

	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> vect(3,100);
	std::cout << "before capacity " << vect.capacity() << std::endl;
	std::cout << "before size " << vect.size() << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator iterator = vect.begin();
	iterator++;
	vect.insert(iterator, 3, 666);
	std::cout << "after capacity " << vect.capacity() << std::endl;
	std::cout << "after size " << vect.size() << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator check;
	TESTED_NAMESPACE::vector<int>::iterator checkend = vect.end();
	for(check = vect.begin(); check != checkend; ++check)
	{
		std::cout << (*check) << std::endl;
	}

	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> anothervector (4,400);
	iterator = vect.begin();
	check = anothervector.begin();
	checkend = anothervector.end();
	vect.insert(iterator, check, checkend);
	checkend = vect.end();
	for(iterator = vect.begin(); iterator != checkend; ++iterator)
	{
		std::cout << (*iterator) << std::endl;
	}

	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> myvector_test;
	for (int i=1; i<=10; i++)
		myvector_test.push_back(i);
	TESTED_NAMESPACE::vector<int>::iterator return_value = myvector_test.erase (myvector_test.begin()+5);
	std::cout << "return_value : " << (*return_value) << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator CHECK;
	TESTED_NAMESPACE::vector<int>::iterator CHECKEND = myvector_test.end();
	for(CHECK = myvector_test.begin(); CHECK != CHECKEND; ++CHECK)
	{
		std::cout << (*CHECK) << std::endl;
	}

	std::cout << "before capacity " << myvector_test.capacity() << std::endl;
	std::cout << "before size " << myvector_test.size() << std::endl;
	return_value =  myvector_test.erase (myvector_test.begin(),myvector_test.begin()+3);
	std::cout << "return_value : " << (*return_value) << std::endl;
	std::cout << "after capacity " << myvector_test.capacity() << std::endl;
	std::cout << "after size " << myvector_test.size() << std::endl;
	CHECKEND = myvector_test.end();
	for(CHECK = myvector_test.begin(); CHECK != CHECKEND; ++CHECK)
	{
		std::cout << (*CHECK) << std::endl;
	}

	std::cout << "-------------------------------------" << std::endl;
	TESTED_NAMESPACE::vector<int> foo (3,100);
	TESTED_NAMESPACE::vector<int> bar (5,200);
	std::cout << "BEFORE : foo capacity " << foo.capacity() << " foo size " << foo.size() << std::endl;
	std::cout << "bar capacity " << bar.capacity() << " bar size " << bar.size() << std::endl;
	foo.swap(bar);

	TESTED_NAMESPACE::vector<int>::iterator foo_it;
	TESTED_NAMESPACE::vector<int>::iterator foo_ite = foo.end();
	for (foo_it = foo.begin(); foo_it != foo_ite; ++foo_it)
		std::cout << "foo: " << (*foo_it) << std::endl;

	std::cout << std::endl;
	TESTED_NAMESPACE::vector<int>::iterator bar_it;
	TESTED_NAMESPACE::vector<int>::iterator bar_ite = bar.end();
	for (bar_it = bar.begin(); bar_it != bar_ite; ++bar_it)
		std::cout << "bar: " << (*bar_it) << std::endl;
	std::cout << "AFTER : foo capacity " << foo.capacity() << " foo size " << foo.size() << std::endl;
	std::cout << "bar capacity " << bar.capacity() << " bar size " << bar.size() << std::endl;

	TESTED_NAMESPACE::vector<int> foo_b (3,100);
	TESTED_NAMESPACE::vector<int> bar_b (foo_b);
	foo_b.swap(bar_b);
	foo_ite = foo_b.end();
	for (foo_it = foo_b.begin(); foo_it != foo_ite; ++foo_it)
		std::cout << "foo_b: " << (*foo_it) << std::endl;

	std::cout << std::endl;
	bar_ite = bar_b.end();
	for (bar_it = bar_b.begin(); bar_it != bar_ite; ++bar_it)
		std::cout << "bar_b: " << (*bar_it) << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "foo capacity " << foo.capacity() << " foo size " << foo.size() << std::endl;
	foo_ite = foo.end();
	for (foo_it = foo.begin(); foo_it != foo_ite; ++foo_it)
		std::cout << "before clear : foo: " << (*foo_it) << std::endl;
	foo.clear();
	std::cout << "foo capacity " << foo.capacity() << " foo size " << foo.size() << std::endl;
	foo.push_back(1);
	foo.push_back(2);
	foo_ite = foo.end();
	for (foo_it = foo.begin(); foo_it != foo_ite; ++foo_it)
		std::cout << "after clear : foo: " << (*foo_it) << std::endl;
	std::cout << "foo capacity " << foo.capacity() << " foo size " << foo.size() << std::endl;
}
