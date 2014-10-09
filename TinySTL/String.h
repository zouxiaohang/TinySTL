#ifndef _STRING_H_
#define _STRING_H_

#include "Allocator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"

#include <cstring>
#include <type_traits>

namespace TinySTL{
	
	//the class of string
	class string{
	public:
		typedef char			value_type;
		typedef char *			iterator;
		typedef const char *	const_iterator;
		typedef reverse_iterator<char*> reverse_iterator;
		typedef const reverse_iterator const_reverse_iterator;
		typedef char&			reference;
		typedef const char&		const_reference;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;
		//npos is a static member constant value with the greatest possible value for an element of type size_t.
		static const size_t npos = -1;
	private:
		char *start_;
		char *finish_;
		char *endOfStorage_;

		typedef TinySTL::allocator<char> dataAllocator;
	public:
		string() :start_(0), finish_(0), endOfStorage_(0){}
		string(const string& str);
		string(const string& str, size_t pos, size_t len = npos);
		string(const char* s);
		string(const char* s, size_t n);
		string(size_t n, char c);
		template <class InputIterator>
		string(InputIterator first, InputIterator last);

		string& operator= (const string& str);
		string& operator= (const char* s);
		string& operator= (char c);

		~string(){ destroyAndDeallocate(); }

		iterator begin(){ return start_; }
		const_iterator begin() const{ return start_; }
		iterator end(){ return finish_; }
		const_iterator end() const{ return finish_; }
		reverse_iterator rbegin(){ return reverse_iterator(start_); }
		const_reverse_iterator rbegin() const{ return reverse_iterator(start_); }
		reverse_iterator rend(){ return reverse_iterator(finish_); }
		const_reverse_iterator rend() const{ return reverse_iterator(finish_); }
		/*const_iterator cbegin() const{ return start_; }
		const_iterator cend() const{ return finish_; }
		const_reverse_iterator crbegin() const{ return reverse_iterator(start_); }
		const_reverse_iterator crend() const{ return reverse_iterator(finish_); }*/
		size_t size() const{ return finish_ - start_; }
		size_t length() const{ return size(); }
		size_t capacity() const{ return endOfStorage_ - start_; }
		void clear(){
			dataAllocator::destroy(start_, finish_);
			start_ = finish_;
		}
		bool empty() const{ return begin() == end(); }
		void resize(size_t n);//TODO
		void resize(size_t n, char c);//TODO
		void reserve(size_t n = 0);//TODO
		void shrink_to_fit(){ dataAllocator::deallocate(finish_, endOfStorage_ - finish_); }
	private:
		void allocateAndFillN(size_t n, char c){
			start_ = dataAllocator::allocate(n);
			finish_ = TinySTL::uninitialized_fill_n(start_, n, c);
			endOfStorage_ = finish_;
		}
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last){
			start_ = dataAllocator::allocate(last - first);
			finish_ = TinySTL::uninitialized_copy(first, last, start_);
			endOfStorage_ = finish_;
		}
		void string_aux(size_t n, char c, std::true_type){
			allocateAndFillN(n, c);
		}
		template<class InputIterator>
		void string_aux(InputIterator first, InputIterator last, std::false_type){
			allocateAndCopy(first, last);
		}
		void destroyAndDeallocate(){
			dataAllocator::destroy(start_, finish_);
			dataAllocator::deallocate(start_, endOfStorage_ - start_);
		}
	};
	const size_t string::npos;

	string::string(size_t n, char c){
		allocateAndFillN(n, c);
	}
	template<class InputIterator>
	string::string(InputIterator first, InputIterator last){
		//处理指针和数字间的区别的函数
		string_aux(first, last, typename std::is_integral<InputIterator>::type());
	}
	string::string(const char* s){
		allocateAndCopy(s, s + strlen(s));
	}
	string::string(const char* s, size_t n){
		allocateAndCopy(s, s + n);
	}
	string::string(const string& str){
		allocateAndCopy(str.start_, str.finish_);
	}
	string::string(const string& str, size_t pos, size_t len){
		allocateAndCopy(str.start_ + pos, str.start_ + pos + len);
	}
	string& string::operator= (const string& str){
		if (this != &str){
			destroyAndDeallocate();
			allocateAndCopy(str.start_, str.finish_);
		}
		return *this;
	}
	string& string::operator= (const char* s){
		destroyAndDeallocate();
		allocateAndCopy(s, s + strlen(s));
		return *this;
	}
	string& string::operator= (char c){
		destroyAndDeallocate();
		allocateAndFillN(1, c);
		return *this;
	}
}
#endif