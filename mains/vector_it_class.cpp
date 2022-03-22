#include "../stack.hpp"
#include "../iterator_vector.hpp"
#include "../vector.hpp"
#include <vector>
#include <iostream>
class Yolo
{
	public:
		Yolo(void)
		{
			this->_value = 0;
		}
		Yolo(float f) : _value(f)
		{
		}
		~Yolo(void)
		{
		}
		Yolo(Yolo const & src)
		{
			*this = src;
		}
		Yolo & operator=(Yolo const & rhs)
		{
			this->_value = rhs.get_value();
			return *this;
		}
		float		get_value(void) const
		{
			return this->_value;
		}
	private:
		float _value;
};

int main()
{	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::vector<Yolo*> test;
	Yolo* A = new Yolo(1.1f);
	Yolo* B = new Yolo(2.2f);
	Yolo* C = new Yolo(3.3f);
	Yolo* D = new Yolo(4.4f);
	Yolo* E = new Yolo(5.5f);
	Yolo* F = new Yolo(6.6f);
	Yolo* G = new Yolo(7.7f);
	Yolo* H = new Yolo(8.8f);
	Yolo* I = new Yolo(9.9f);

	test.push_back(A);
	test.push_back(B);
	test.push_back(C);
	test.push_back(D);
	test.push_back(E);
	test.push_back(F);
	test.push_back(G);
	test.push_back(H);
	test.push_back(I);
	
	TESTED_NAMESPACE::vector<Yolo*>::iterator it;
	TESTED_NAMESPACE::vector<Yolo*>::iterator ite = test.end();
	for(it = test.begin(); it != ite; ++it)
	{
		std::cout << "test for loop : " << (*it)->get_value() << std::endl;
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
	std::cout << "test begin: " << (*it)->get_value() << std::endl;
	it++;
	std::cout << "it++: " << (*it)->get_value() << std::endl;
	++it;
	std::cout << "++it: " << (*it)->get_value() << std::endl;
	it--;
	std::cout << "it--: " << (*it)->get_value() << std::endl;
	--it;
	std::cout << "--it: " << (*it)->get_value() << std::endl;
	it += 3;
	std::cout << "it += 3: " << (*it)->get_value() << std::endl;
	it -= 2;
	std::cout << "it -= 2: " << (*it)->get_value() << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	it = test.begin() + 3;
	std::cout << "test.begin() + 3: " << (*it)->get_value() << std::endl;
	ite = test.end() - 3;
	std::cout << "test.end() - 3: " << (*ite)->get_value() << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	it = test.begin();
	ite = test.end();
	std::cout << "ite - it : " << ite - it << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	it = test.begin();
	std::cout << "it[4] : " << it[4]->get_value() << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	it = test.begin();
	ite = test.end();
	Yolo* yo = new Yolo(666.666f);
	(*it) = yo;
	it++;
	Yolo* yoo = new Yolo(-1212.1f);
	(*it) = yoo;
	for(it = test.begin(); it != ite; ++it)
	{
		std::cout << "test for non constness : " << (*it)->get_value() << std::endl;
	}

	delete A;
	delete B;
	delete C;
	delete D;
	delete E;
	delete F;
	delete G;
	delete H;
	delete I;
	delete yo;
	delete yoo;
	
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~const_iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::vector<Yolo*> test_const;
	Yolo* Aa = new Yolo(1.1f);
	Yolo* Ba = new Yolo(2.2f);
	Yolo* Ca = new Yolo(3.3f);
	Yolo* Da = new Yolo(4.4f);
	Yolo* Ea = new Yolo(5.5f);
	Yolo* Fa = new Yolo(6.6f);
	Yolo* Ga = new Yolo(7.7f);
	Yolo* Ha = new Yolo(8.8f);
	Yolo* Ia = new Yolo(9.9f);

	test_const.push_back(Aa);
	test_const.push_back(Ba);
	test_const.push_back(Ca);
	test_const.push_back(Da);
	test_const.push_back(Ea);
	test_const.push_back(Fa);
	test_const.push_back(Ga);
	test_const.push_back(Ha);
	test_const.push_back(Ia);
	
	TESTED_NAMESPACE::vector<Yolo*>::iterator begi;
	TESTED_NAMESPACE::vector<Yolo*>::iterator endi = test_const.end();
	for(begi = test_const.begin(); begi != endi; ++begi)
	{
		std::cout << "test_const for loop : " << (*begi)->get_value() << std::endl;
	}
	std::cout << "----------------------------------------------------------" << std::endl;
	
	begi = test_const.begin();
	endi = test_const.end();
	endi--;
	std::cout << "begi == endi: " << (begi == endi) << std::endl;
	std::cout << "begi != endi: " << (begi != endi) << std::endl;
	std::cout << "begi < endi: " << (begi < endi) << std::endl;
	std::cout << "begi > endi: " << (begi > endi) << std::endl;
	std::cout << "begi <= endi: " << (begi <= endi) << std::endl;
	std::cout << "begi >= endi: " << (begi >= endi) << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	begi = test_const.begin();
	endi = test_const.end();
	std::cout << "test_const begin: " << (*begi)->get_value() << std::endl;
	begi++;
	std::cout << "begi++: " << (*begi)->get_value() << std::endl;
	++begi;
	std::cout << "++begi: " << (*begi)->get_value() << std::endl;
	begi--;
	std::cout << "begi--: " << (*begi)->get_value() << std::endl;
	--begi;
	std::cout << "--begi: " << (*begi)->get_value() << std::endl;
	begi += 3;
	std::cout << "begi += 3: " << (*begi)->get_value() << std::endl;
	begi -= 2;
	std::cout << "begi -= 2: " << (*begi)->get_value() << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	begi = test_const.begin() + 3;
	std::cout << "test_const.begin() + 3: " << (*begi)->get_value() << std::endl;
	endi = test_const.end() - 3;
	std::cout << "test_const.end() - 3: " << (*endi)->get_value() << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	begi = test_const.begin();
	endi = test_const.end();
	std::cout << "endi - begi : " << endi - begi << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	begi = test_const.begin();
	std::cout << "begi[4] : " << begi[4]->get_value() << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;

	delete Aa;
	delete Ba;
	delete Ca;
	delete Da;
	delete Ea;
	delete Fa;
	delete Ga;
	delete Ha;
	delete Ia;

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~reverse_iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::vector<Yolo*> testreverse;
	Yolo* Ab = new Yolo(1.1f);
	Yolo* Bb = new Yolo(2.2f);
	Yolo* Cb = new Yolo(3.3f);
	Yolo* Db = new Yolo(4.4f);
	Yolo* Eb = new Yolo(5.5f);
	Yolo* Fb = new Yolo(6.6f);
	Yolo* Gb = new Yolo(7.7f);
	Yolo* Hb = new Yolo(8.8f);
	Yolo* Ib = new Yolo(9.9f);
	testreverse.push_back(Ab);
	testreverse.push_back(Bb);
	testreverse.push_back(Cb);
	testreverse.push_back(Db);
	testreverse.push_back(Eb);
	testreverse.push_back(Fb);
	testreverse.push_back(Gb);
	testreverse.push_back(Hb);
	testreverse.push_back(Ib);

	TESTED_NAMESPACE::vector<Yolo*>::reverse_iterator rit;
	TESTED_NAMESPACE::vector<Yolo*>::reverse_iterator rite = testreverse.rend();
	for(rit = testreverse.rbegin(); rit != rite; ++rit)
	{
		std::cout << "test for loop : " << (*rit)->get_value() << std::endl;
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
	std::cout << "test rbegin: " << (*rit)->get_value() << std::endl;
	rit++;
	std::cout << "rit++: " << (*rit)->get_value() << std::endl;
	++rit;
	std::cout << "++rit: " << (*rit)->get_value() << std::endl;
	rit--;
	std::cout << "rit--: " << (*rit)->get_value() << std::endl;
	--rit;
	std::cout << "--rit: " << (*rit)->get_value() << std::endl;
	rit += 3;
	std::cout << "rit += 3: " << (*rit)->get_value() << std::endl;
	rit -= 2;
	std::cout << "rit -= 2: " << (*rit)->get_value() << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	rit = testreverse.rbegin() + 3;
	std::cout << "testreverse.rbegin() + 3: " << (*rit)->get_value() << std::endl;
	rite = testreverse.rend() - 3;
	std::cout << "testreverse.rend() - 3: " << (*rite)->get_value() << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	rit = testreverse.rbegin();
	rite = testreverse.rend();
	std::cout << "rite - rit : " << rite - rit << std::endl;
	rite -= 5;
	std::cout << "rite - rit : " << rite - rit << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	rit = testreverse.rbegin();
	std::cout << "rit[4] : " << rit[4]->get_value() << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	rit = testreverse.rbegin();
	rite = testreverse.rend();
	Yolo* a = new Yolo(666.666f);
	(*rit) = a;
	rit++;
	Yolo* b = new Yolo(77.88f);
	(*rit) = b;
	for(rit = testreverse.rbegin(); rit != rite; ++rit)
	{
		std::cout << "test for non constness : " << (*rit)->get_value() << std::endl;
	}

	delete Ab;
	delete Bb;
	delete Cb;
	delete Db;
	delete Eb;
	delete Fb;
	delete Gb;
	delete Hb;
	delete Ib;
	delete a;
	delete b;

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~const_reverse_iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TESTED_NAMESPACE::vector<Yolo*> testconstreverse;
	Yolo* Ac = new Yolo(1.1f);
	Yolo* Bc = new Yolo(2.2f);
	Yolo* Cc = new Yolo(3.3f);
	Yolo* Dc = new Yolo(4.4f);
	Yolo* Ec = new Yolo(5.5f);
	Yolo* Fc = new Yolo(6.6f);
	Yolo* Gc = new Yolo(7.7f);
	Yolo* Hc = new Yolo(8.8f);
	Yolo* Ic = new Yolo(9.9f);
	testconstreverse.push_back(Ac);
	testconstreverse.push_back(Bc);
	testconstreverse.push_back(Cc);
	testconstreverse.push_back(Dc);
	testconstreverse.push_back(Ec);
	testconstreverse.push_back(Fc);
	testconstreverse.push_back(Gc);
	testconstreverse.push_back(Hc);
	testconstreverse.push_back(Ic);

	TESTED_NAMESPACE::vector<Yolo*>::reverse_iterator crit;
	TESTED_NAMESPACE::vector<Yolo*>::reverse_iterator crite = testconstreverse.rend();
	for(crit = testconstreverse.rbegin(); crit != crite; ++crit)
	{
		std::cout << "test for loop : " << (*crit)->get_value() << std::endl;
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
	std::cout << "test rbegin: " << (*crit)->get_value() << std::endl;
	crit++;
	std::cout << "crit++: " << (*crit)->get_value() << std::endl;
	++crit;
	std::cout << "++crit: " << (*crit)->get_value() << std::endl;
	crit--;
	std::cout << "crit--: " << (*crit)->get_value() << std::endl;
	--crit;
	std::cout << "--crit: " << (*crit)->get_value() << std::endl;
	crit += 3;
	std::cout << "crit += 3: " << (*crit)->get_value() << std::endl;
	crit -= 2;
	std::cout << "crit -= 2: " << (*crit)->get_value() << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	crit = testconstreverse.rbegin() + 3;
	std::cout << "testconstreverse.rbegin() + 3: " << (*crit)->get_value() << std::endl;
	crite = testconstreverse.rend() - 3;
	std::cout << "testconstreverse.rend() - 3: " << (*crite)->get_value() << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	crit = testconstreverse.rbegin();
	crite = testconstreverse.rend();
	std::cout << "crite - crit : " << crite - crit << std::endl;
	crite -= 5;
	std::cout << "crite - crit : " << crite - crit << std::endl;

	std::cout << "----------------------------------------------------------" << std::endl;
	crit = testconstreverse.rbegin();
	std::cout << "crit[4] : " << crit[4]->get_value() << std::endl;

	delete Ac;
	delete Bc;
	delete Cc;
	delete Dc;
	delete Ec;
	delete Fc;
	delete Gc;
	delete Hc;
	delete Ic;

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}
