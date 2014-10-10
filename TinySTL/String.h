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
		reverse_iterator rbegin(){ return reverse_iterator(finish_); }
		const_reverse_iterator rbegin() const{ return const_reverse_iterator(finish_); }
		reverse_iterator rend(){ return reverse_iterator(start_); }
		const_reverse_iterator rend() const{ return const_reverse_iterator(start_); }
		const_iterator cbegin() const{ return start_; }
		const_iterator cend() const{ return finish_; }
		const_reverse_iterator crbegin() const{ return const_reverse_iterator(finish_); }
		const_reverse_iterator crend() const{ return const_reverse_iterator(start_); }
		size_t size() const{ return finish_ - start_; }
		size_t length() const{ return size(); }
		size_t capacity() const{ return endOfStorage_ - start_; }
		void clear(){
			dataAllocator::destroy(start_, finish_);
			start_ = finish_;
		}
		bool empty() const{ return begin() == end(); }
		void resize(size_t n);
		void resize(size_t n, char c);
		void reserve(size_t n = 0);
		void shrink_to_fit(){ 
			dataAllocator::deallocate(finish_, endOfStorage_ - finish_); 
			endOfStorage_ = finish_;
		}

		char& operator[] (size_t pos){ return *(start_ + pos); }
		const char& operator[] (size_t pos) const{ return (*this)[pos]; }
		char& back(){ return *(finish_ - 1); }
		const char& back() const{ return back(); }
		char& front(){ return *(start_); }
		const char& front() const{ return front(); }
	private:
		size_type getNewCapacity(size_type len)const{
			size_type oldCapacity = endOfStorage_ - start_;
			auto res = std::max(oldCapacity, len);
			size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : 1);
			return newCapacity;
		}
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
	void string::resize(size_t n){
		resize(n, value_type());
	}
	void string::resize(size_t n, char c){
		if (n < size()){
			dataAllocator::destroy(start_ + n, finish_);
			finish_ = start_ + n;
		}else if (n > size() && n <= capacity()){
			auto lengthOfInsert = n - size();
			finish_ = TinySTL::uninitialized_fill_n(finish_, lengthOfInsert, c);
		}
		else if (n > capacity()){
			auto lengthOfInsert = n - size();
			iterator newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert));
			iterator newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
			newFinish = TinySTL::uninitialized_fill_n(newFinish, lengthOfInsert, c);

			destroyAndDeallocate();
			start_ = newStart;
			finish_ = newFinish;
			endOfStorage_ = start_ + n;
		}
	}
	void string::reserve(size_t n){
		if (n <= capacity())
			return;
		iterator newStart = dataAllocator::allocate(n);
		iterator newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + n;
	}
}
#endif