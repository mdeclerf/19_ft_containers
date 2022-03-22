#ifndef UTILS_HPP
#define UTILS_HPP

#include <type_traits>

namespace ft
{
	//---------------------------------enable if---------------------------------
	//https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/enable-if
	template <bool, class T = void> 
	struct enable_if 
	{};

	template <class T> 
	struct enable_if<true, T> 
	{ 
	typedef T type; 
	};

	//---------------------------------is Integral---------------------------------
	// https://en.cppreference.com/w/cpp/types/is_integral
	template<typename T>
	struct is_Integral
	{
		static const bool value = false;
	};

	template<>
	struct is_Integral<char>
	{
		static const bool value = true;
	};

	template<>
	struct is_Integral<char32_t>
	{
		static const bool value = true;
	};

	template<>
	struct is_Integral<wchar_t>
	{
		static const bool value = true;
	};

	template<>
	struct is_Integral<signed char>
	{
		static const bool value = true;
	};

		template<>
	struct is_Integral<signed short int>
	{
		static const bool value = true;
	};

	template<>
	struct is_Integral<signed int>
	{
		static const bool value = true;
	};

		template<>
	struct is_Integral<signed long int>
	{
		static const bool value = true;
	};

	template<>
	struct is_Integral<signed long long int>
	{
		static const bool value = true;
	};

		template<>
	struct is_Integral<unsigned char>
	{
		static const bool value = true;
	};

	template<>
	struct is_Integral<unsigned short int>
	{
		static const bool value = true;
	};

		template<>
	struct is_Integral<unsigned int>
	{
		static const bool value = true;
	};

	template<>
	struct is_Integral<unsigned long int>
	{
		static const bool value = true;
	};

		template<>
	struct is_Integral<unsigned long long int>
	{
		static const bool value = true;
	};

	template<>
	struct is_Integral<bool>
	{
		static const bool value = true;
	};

	//---------------------------------pair---------------------------------
	// https://www.cplusplus.com/reference/utility/pair/
	// https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a02030.html
	template<class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(), second() {}

		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	//---------------------------------make pair---------------------------------
	// https://www.cplusplus.com/reference/utility/make_pair/
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}

	//---------------------------------lexicographical compare---------------------------------
	// https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1!=last1)
		{
			if (first2==last2 || !comp(*first2, *first1)) return false;
			else if (!comp(*first2, *first1)) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
}

#endif