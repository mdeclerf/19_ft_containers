#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "iterator_vector.hpp"
#include "vector.hpp"

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			//----------------------------------------canon----------------------------------------
			typedef size_t			size_type;
			typedef T				value_type;
			typedef Container		container_type;
			
			explicit stack(const container_type& ctnr = container_type())
			{
				this->c = ctnr;
			}

			stack(stack<T > const &src)
			{
				this->c = src.c;
			}

			~stack()
			{
			}

			stack<T> const &operator=(stack<T> const &rhs)
			{
				this->c = rhs.c;
				return(*this);
			}
			//----------------------------------------getter----------------------------------------
			container_type &get_c(void)
			{
				return (this->c);
			}
			//----------------------------------------ft----------------------------------------
			bool empty() const
			{
				return (this->c.empty());
			}

			size_type size(void) const
			{
				return (this->c.size());
			}

			value_type& top()
			{
				return (this->c.back());
			}

			const value_type& top() const
			{
				return (this->c.back());
			}

			void push (const value_type& val)
			{
				this->c.push_back(val);
			}

			void pop(void)
			{
				this->c.pop_back();
			}

		protected:
			container_type		c;
		
		private:
			template <class Type, class Cont>
			friend bool operator== (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs);
			
			template <class Type, class Cont>
			friend bool operator!= (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs);
			
			template <class Type, class Cont>
			friend bool operator<	(const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs);

			template <class Type, class Cont>
			friend bool operator<= (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs);

			template <class Type, class Cont>
			friend bool operator>	(const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs);

			template <class Type, class Cont>
			friend bool operator>= (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs);
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class T, class Container>
	bool operator<	(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
	bool operator>	(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif