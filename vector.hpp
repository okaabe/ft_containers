/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:29:31 by ahamdy            #+#    #+#             */
/*   Updated: 2023/02/12 12:55:21y adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<memory>
#include<iostream>
#include "vector_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include "reverse_iterator.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
	// ************* TYPES ***********************
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef T value_type;
		typedef typename ft::vector_iterator<T*> iterator;
		typedef typename ft::const_vector_iterator<const T*> const_iterator;
		typedef std::size_t size_type;
		typedef  ptrdiff_t difference_type;
		typedef Allocator allocator_type;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	private :
		size_type _size;
		size_type _capacity;
		value_type*	_array;
		allocator_type _alloc;
	public :
	// *********** CONSTRUCTORS/DISTRUCTOR ****************
		explicit vector (const allocator_type& alloc = allocator_type()) : _size() , _capacity(), _array() , _alloc(alloc)
		{}
		explicit vector(size_type n, const T& value = T(),
		const allocator_type& alloc = allocator_type()) : _size() , _capacity(), _array() , _alloc(alloc)
		{
			value_type *new_type = _alloc.allocate(n);
            for (size_t i = 0; i < n; i++)
            {
                _alloc.construct(new_type  + i, value);
            }
            for (size_t i = 0; i < _size; i++)
                _alloc.destroy(_array + i);
            _alloc.deallocate(_array, _capacity);
            _array = new_type;
            _capacity = n;
            _size = n;
	}
		template <class InputIterator>
		vector(typename ft::enable_if<(!ft::is_integral<InputIterator>::value), InputIterator>::type first, InputIterator last,
		const allocator_type& alloc  = allocator_type()) : _size() , _capacity() , _array() , _alloc(alloc)
		{
            size_t n = 0;
            InputIterator tmp_first = first;
            while (tmp_first != last)
            {
                n += 1;
                tmp_first += 1;
            }
			value_type *new_type = _alloc.allocate(n);
            for (size_t i = 0; i < n; i++)
            {
                _alloc.construct(new_type  + i, *first);
				first++;
            }
            for (size_t i = 0; i < _size; i++)
                _alloc.destroy(_array + i);
            _alloc.deallocate(_array, _capacity);
            _array = new_type;
            _capacity = n;
            _size = n;
		}
		vector(const vector<T,Allocator>& x) :  _size() , _capacity() , _array()
		{
			*this = x;
		}
		~vector()
		{
			 for (size_t i = 0; i < _size; i++)
                _alloc.destroy(_array + i);
            _alloc.deallocate(_array, _capacity);
		}
		vector<value_type ,allocator_type>& operator=(const vector<value_type> &x)
		{
			if (_capacity < x.size())
			{
				value_type *new_type = _alloc.allocate(x._size);
                for (size_t i = 0; i < x._size; i++)
                {
                    _alloc.construct(new_type  + i, x._array[i]);
                }
                for (size_t i = 0; i < size(); i++)
                    _alloc.destroy(_array + i);
                _alloc.deallocate(_array, _capacity);
                _array = new_type;
                _capacity = x._size;
                _size = x._size;
			}
			else
			{
				for (size_t i = 0; i < x._size; i++)
					_array[i] = x._array[i];
				_size = x._size;
			}
			return (*this);
		}
		void assign(size_type n, const value_type& u)
        {
            if (n > _capacity)
            {
                value_type *new_type = _alloc.allocate(n);
                for (size_t i = 0; i < n; i++)
                {
                    _alloc.construct(new_type  + i, u);
                }
                for (size_t i = 0; i < _size; i++)
                    _alloc.destroy(_array + i);
                _alloc.deallocate(_array, _capacity);
                _array = new_type;
                _capacity = n;
                _size = n;
            }   
            else
            {
                for (size_t i = 0; i < n; i++)
                {
                    _alloc.construct(_array + i, u);
                }
                _size = n;
            }
        }
        template <class InputIterator>
        void assign(typename ft::enable_if<(!ft::is_integral<InputIterator>::value), InputIterator>::type first, InputIterator last)
        {
            size_t n = 0;
            InputIterator tmp_first = first;
			const value_type &u = *first;
            while (tmp_first != last)
            {
                n += 1;
                tmp_first = tmp_first + 1;
            }
            if (n > _capacity)
            {
                value_type *new_type = _alloc.allocate(n);
                for (size_t i = 0; i < n; i++)
                {
					_alloc.construct(new_type  + i, u);
				}
                for (std::size_t i = 0; i < _size; i++)
                    _alloc.destroy(_array + i);
                _alloc.deallocate(_array, _capacity);
                _array = new_type;
                _capacity = n;
                _size = n;
            }    
            else
            {
                for (size_t i = 0; i < n; i++)
					*(_array + i)  = *first;
                _size = n;
            }
        }
		allocator_type get_allocator() const
		{ return _alloc;}
	// ******** ITERATORS ************
		iterator begin()
		{
			return (iterator(_array));
		}
		const_iterator begin() const
		{
			return (const_iterator(_array));
		}
		const_iterator end() const
		{
			if (this->empty())
				return (begin());
			return (const_iterator(_array + size()));
		}
		iterator end()
		{
			if (this->empty())
				return (begin());
			return (iterator(_array + size()));
		}
		reverse_iterator rbegin()
		{
			if (this->empty())
				return (rend());
			return (reverse_iterator(_array + _size - 1));
		}
		const_reverse_iterator rbegin() const
		{
			if (this->empty)
				return (rend());
			return (const_reverse_iterator(_array + _size - 1));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(_array));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(_array));	
		}
	// ************ capacity *****************
	 		size_type size() const
			{ return (_size); }
			size_type max_size() const
			{ return _alloc.max_size();}
			void resize(size_type n, value_type c = value_type())
			{
       			 while (size() < n) {
       			     push_back(c);
       			 }

       			 while (size() > n) {
       			     pop_back();
       			 }
			}
			size_type capacity() const
			{ return (_capacity);}
			bool empty() const
			{
				if (!_size)
					return (1);
				return (0);
			}
			void reserve(size_type n)
			{
				if (n <= _capacity) return;
				value_type *new_data = _alloc.allocate(n);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(new_data + i, std::move(_array[i]));
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_array + i);
				_alloc.deallocate(_array, _capacity);
				_array = new_data;
				this->_capacity = n;
			}
	// ************** ELEMENT ACCESS ****************
		reference operator[](size_type n)
		{ return (_array[n]); }
		const_reference operator[](size_type n) const
		{ return (_array[n]); }
		const_reference at(size_type n) const
		

{
			if (n >= _size)
				throw std::out_of_range("out of range");
			return (this->operator[](n));
		}
		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("out of range");
			return (this->operator[](n));
		}
		reference front()
		{
			return (*_array);
		}
		const_reference front() const
		{
			return(*_array);
		}
		reference back()
		{
			return (*(_array + size() - 1));
		}
		const_reference back() const
		{
			return (*(_array + size() + 1));
		}	
		
	// ************ MODIFIERS ******************
		void push_back(const value_type& x)
		{
			if (_size == _capacity)
			{
				if (!_capacity)
					_capacity += 1;
				this->reserve(_capacity * 2);
			}
			_array[_size] = x;
			_size += 1;
		}
		void pop_back()
		{
			_alloc.destroy(_array + (_size - 1));
			_size -= 1;

		}
		iterator insert(iterator position, const value_type& x)
		{
			int p_index = position - begin();
			insert(position, 1, x);
			return (begin() + p_index);
		}
		void insert(iterator position, size_type n, const T& x)
		{
			size_t p_index = position - begin();
			// value_type tmp;

			if (position < begin() || position > end())
				*position;
			else if (_size + n > _capacity || position == this->end())
			{
				int allocated_size = 0;
				if (_size + n > _size * 2)
					allocated_size = _size + n;
				else
					allocated_size = _size * 2;
				value_type *new_data = _alloc.allocate(allocated_size);
				size_t i_2 = 0;
				for (size_t i = 0; i_2 < _size + n; i++)
				{
					if (p_index  == i_2)
					{
						for (size_t j = 0; j < n; j++)
            {
             _alloc.construct(new_data + i_2, x);
                i_2++;
            }
            i_2--;
            i--;
					}
			else
				_alloc.construct(new_data + i_2, _array[i]);
				i_2++;
			}
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_array + i);
				_alloc.deallocate(_array, _capacity);
				_array = new_data;
				_size += n;
				_capacity = allocated_size;
			}
			else
			{
       int i = _size - 1;
			   for (iterator it = end() + n - 1; it >= end(); it--)	
        {
            *it = *(_array + i);
			*position = x;
          i--;
        }
		_size += n;
		}
  }
  	template <class InputIterator>
		void insert(iterator position,
		typename ft::enable_if<!(ft::is_integral<InputIterator>::value), InputIterator>::type first, InputIterator last)	
		{
			size_t n = 0;
			InputIterator tmp_first = first;
			int p_index = position - begin();
			while (tmp_first != last)
			{
				n += 1;
				tmp_first += 1;
			}
			value_type tmp;

			if (position < begin() || position > end())
				*position;
			else if (_size + n > _capacity || position == this->end())
			{
				int allocated_size = 0;
				if (_size + n > _size * 2)
					allocated_size = _size + n;
				else
					allocated_size = _size * 2;
				value_type *new_data = _alloc.allocate(allocated_size);
				int i_2 = 0;
				for (size_t i = 0; i_2 < _size + n; i++)
				{
					if (p_index  == i_2)
					{
						for (size_t j = 0; j < n; j++)
            {
             _alloc.construct(new_data + i_2, *first);
			 first++;
                i_2++;
            }
            i_2--;
            i--;
					}
					else 
					_alloc.construct(new_data + i_2, std::move(_array[i]));
					i_2++;
				}
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_array + i);
				_alloc.deallocate(_array, _capacity);
				_array = new_data;
				_size += n;
				_capacity = allocated_size;
			}
			else
			{
       int i = 0;
      i = (end() - 1) - begin();
			   for (iterator it = end() + n - 1; it >= end(); it--)	
        {
            *it = *(_array + i);
          i--;
        }
      for (iterator it = position; it < position + n; it++)
      {
          *it = *first;
		  first++;
	}
  }
		/*	******* functions start ***********/
		}
		iterator erase (iterator first, iterator last)
		{
			int p_index = first - begin();

			if (last == end())
			{
				while (first < last)
				{
					last--;
					pop_back();
				}
     			 return (end());
			}
			else
			{
				iterator tmp_first = first;
				for (iterator it  = last; it != end(); it++)
				{
					*tmp_first = *it;
					tmp_first++;
				}
				int n = last - first;
				while (n)
				{
					_alloc.destroy(_array + _size);
					_size--;
					n--;
				}
				return (begin() + p_index);
			}
		}
		iterator erase(iterator position)
		{
			int p_index = position - begin();
			iterator tmp_first = position;
			for (iterator it  = position + 1; it != end(); it++)
			{
				*tmp_first = *it;
				tmp_first++;
			}
			_alloc.destroy(_array + _size);
			_size--;
			return (begin() + p_index);
		}
		void swap(vector<value_type, allocator_type>& copy)
		{
			std::swap(this->_size, copy._size);
			std::swap(this->_capacity, copy._capacity);
			std::swap(this->_array, copy._array);
		}
		void clear()
		{
			int i;

			for (i = 0; i < _size; i++)
				_alloc.destroy(_array + i);
			_size = 0;
		}
		template <class value_type, class allocator_type>  
		friend bool operator> (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second);
		template <class value_type, class allocator_type> 
		friend bool operator!= (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second);		
		template <class value_type, class allocator_type> 
		friend bool operator>= (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second);
		template <class value_type, class allocator_type>
		friend bool operator<= (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second);	
		template <class value_type, class allocator_type>
		friend bool operator< (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second);
		template <class value_type, class allocator_type>
		friend bool operator== (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second);
		template <class value_type, class allocator_type>
		friend void swap (vector<value_type ,allocator_type>& x, vector<value_type,allocator_type>& copy);
};
	// ******************* operators *************
	template <class value_type, class allocator_type>  
		bool operator== (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second)
		{
			return (!((first > second) || first < second));
		}
		template <class value_type, class allocator_type> 
		bool operator!= (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second)
		{ return (!(first == second));}
		template <class value_type, class allocator_type>
		bool operator<  (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second)
		{	
			return ((lexicographical_compare(first.begin(), first.end(), second.begin(), second.end())));
		}
		template <class value_type, class allocator_type> 
		bool operator> (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second)
		{
			return ((lexicographical_compare(second.begin(), second.end(), first.begin(), first.end())));
		}
		template <class value_type, class allocator_type> 
		bool operator<= (const vector<value_type, allocator_type>&first, const vector<value_type,allocator_type>& second)
		{
			return((first < second) || (first == second));
		}
		template <class value_type, class allocator_type>
		bool operator>= (const vector<value_type,allocator_type>& first, const vector<value_type,allocator_type>& second)
		{
			 return ((first > second) || (first == second));
		}
		template <class value_type, class allocator_type>  
		void swap (vector<value_type ,allocator_type>& x, vector<value_type,allocator_type>& copy)
		{
			x.swap(copy);
		}
}
