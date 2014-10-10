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
		const char& operator[] (size_t pos) const{ return *(start_ + pos); }
		char& back(){ return *(finish_ - 1); }
		const char& back() const{ return *(finish_ - 1); }
		char& front(){ return *(start_); }
		const char& front() const{ return *(start_); }

		void push_back(char c){ insert(end(), c); }
		string& insert(size_t pos, const string& str);
		string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);
		string& insert(size_t pos, const char* s);
		string& insert(size_t pos, const char* s, size_t n);
		string& insert(size_t pos, size_t n, char c);
		iterator insert(iterator p, size_t n, char c);
		iterator insert(iterator p, char c);
		template <class InputIterator>
		iterator insert(iterator p, InputIterator first, InputIterator last);
		string& append(const string& str);
		string& append(const string& str, size_t subpos, size_t sublen = npos);
		string& append(const char* s);
		string& append(const char* s, size_t n);
		string& append(size_t n, char c);
		template <class InputIterator>
		string& append(InputIterator first, InputIterator last);
		string& operator+= (const string& str);
		string& operator+= (const char* s);
		string& operator+= (char c);

		void pop_back(){ erase(end() - 1, end()); }
		string& erase(size_t pos = 0, size_t len = npos);
		iterator erase(iterator p);
		iterator erase(iterator first, iterator last);

		string& replace(size_t pos, size_t len, const string& str);
		string& replace(iterator i1, iterator i2, const string& str);
		string& replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos);
		string& replace(size_t pos, size_t len, const char* s);
		string& replace(iterator i1, iterator i2, const char* s);
		string& replace(size_t pos, size_t len, const char* s, size_t n);
		string& replace(iterator i1, iterator i2, const char* s, size_t n);
		string& replace(size_t pos, size_t len, size_t n, char c);
		string& replace(iterator i1, iterator i2, size_t n, char c);
		template <class InputIterator>
		string& replace(iterator i1, iterator i2, InputIterator first, InputIterator last);

		void swap(string& str){
			std::swap(start_, str.start_);
			std::swap(finish_, str.finish_);
			std::swap(endOfStorage_, str.endOfStorage_);
		}
		size_t copy(char* s, size_t len, size_t pos = 0) const{
			auto ptr = TinySTL::uninitialized_copy(begin() + pos, begin() + pos + len, s);
			return (size_t)(ptr - s);
		}

		size_t find(const string& str, size_t pos = 0) const;
		size_t find(const char* s, size_t pos = 0) const;
		size_t find(const char* s, size_t pos, size_t n) const;
		size_t find(char c, size_t pos = 0) const;
		size_t rfind(const string& str, size_t pos = npos) const;
		size_t rfind(const char* s, size_t pos = npos) const;
		size_t rfind(const char* s, size_t pos, size_t n) const;
		size_t rfind(char c, size_t pos = npos) const;
		size_t find_first_of(const string& str, size_t pos = 0) const;
		size_t find_first_of(const char* s, size_t pos = 0) const;
		size_t find_first_of(const char* s, size_t pos, size_t n) const;
		size_t find_first_of(char c, size_t pos = 0) const;
		size_t find_last_of(const string& str, size_t pos = npos) const;
		size_t find_last_of(const char* s, size_t pos = npos) const;
		size_t find_last_of(const char* s, size_t pos, size_t n) const;
		size_t find_last_of(char c, size_t pos = npos) const;
		size_t find_first_not_of(const string& str, size_t pos = 0) const;
		size_t find_first_not_of(const char* s, size_t pos = 0) const;
		size_t find_first_not_of(const char* s, size_t pos, size_t n) const;
		size_t find_first_not_of(char c, size_t pos = 0) const;
		size_t find_last_not_of(const string& str, size_t pos = npos) const;
		size_t find_last_not_of(const char* s, size_t pos = npos) const;
		size_t find_last_not_of(const char* s, size_t pos, size_t n) const;
		size_t find_last_not_of(char c, size_t pos = npos) const;

		string substr(size_t pos = 0, size_t len = npos) const{
			return string(begin() + pos, begin() + pos + len);
		}

		int compare(const string& str) const;
		int compare(size_t pos, size_t len, const string& str) const;
		int compare(size_t pos, size_t len, const string& str,
			size_t subpos, size_t sublen = npos) const;
		int compare(const char* s) const;
		int compare(size_t pos, size_t len, const char* s) const;
		int compare(size_t pos, size_t len, const char* s, size_t n) const;
	private:
		//插入时空间不足的情况
		template<class InputIterator>
		iterator insert_aux_copy(iterator p, InputIterator first, InputIterator last);
		//插入时空间不足的情况
		iterator insert_aux_filln(iterator p, size_t n, value_type c);
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
	};// end of string

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
	template <class InputIterator>
	string::iterator string::insert_aux_copy(iterator p, InputIterator first, InputIterator last){
		size_t lengthOfInsert = last - first;
		auto newCapacity = getNewCapacity(lengthOfInsert);
		iterator newStart = dataAllocator::allocate(newCapacity);
		iterator newFinish = TinySTL::uninitialized_copy(start_, p, newStart);
		newFinish = TinySTL::uninitialized_copy(first, last, newFinish);
		auto res = newFinish;
		newFinish = TinySTL::uninitialized_copy(p, finish_, newFinish);
		
		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + newCapacity;
		return res;
	}
	template <class InputIterator>
	string::iterator string::insert(iterator p, InputIterator first, InputIterator last){
		auto lengthOfLeft = capacity() - size();
		size_t lengthOfInsert = last - first;
		if (lengthOfInsert <= lengthOfLeft){
			auto ptr = finish_;
			for (auto i = lengthOfInsert; i != 0; --i){
				*(finish_ - 1 + i) = *(--ptr);
			}
			TinySTL::uninitialized_copy(first, last, p);
			finish_ += lengthOfInsert;
			return (p + lengthOfInsert);
		}else{
			return insert_aux_copy(p, first, last);
		}
	}
	string& string::insert(size_t pos, const string& str){
		insert(start_ + pos, str.begin(), str.end());
		return *this;
	}
	string& string::insert(size_t pos, const string& str, size_t subpos, size_t sublen){
		insert(begin() + pos, str.begin() + subpos, str.begin() + subpos + sublen);
		return *this;
	}
	string& string::insert(size_t pos, const char* s){
		insert(begin() + pos, s, s + strlen(s));
		return *this;
	}
	string& string::insert(size_t pos, const char* s, size_t n){
		insert(begin() + pos, s, s + n);
		return *this;
	}
	string::iterator string::insert_aux_filln(iterator p, size_t n, value_type c){
		auto newCapacity = getNewCapacity(n);
		iterator newStart = dataAllocator::allocate(newCapacity);
		iterator newFinish = TinySTL::uninitialized_copy(start_, p, newStart);
		newFinish = TinySTL::uninitialized_fill_n(newFinish, n, c);
		auto res = newFinish;
		newFinish = TinySTL::uninitialized_copy(p, finish_, newFinish);

		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + newCapacity;
		return res;
	}
	string& string::insert(size_t pos, size_t n, char c){
		insert(begin() + pos, n, c);
		return *this;
	}
	string::iterator string::insert(iterator p, size_t n, char c){
		auto lengthOfLeft = capacity() - size();
		if (n <= lengthOfLeft){
			auto ptr = finish_;
			for (auto i = n; i != 0; --i){
				*(finish_ - 1 + i) = *(--ptr);
			}
			TinySTL::uninitialized_fill_n(p, n, c);
			finish_ += n;
			return (p + n);
		}else{
			return insert_aux_filln(p, n, c);
		}
	}
	string::iterator string::insert(iterator p, char c){
		return insert(p, 1, c);
	}
	string& string::operator+= (const string& str){
		insert(size(), str);
		return *this;
	}
	string& string::operator+= (const char* s){
		insert(size(), s);
		return *this;
	}
	string& string::operator+= (char c){
		insert(end(), c);
		return *this;
	}
	string& string::append(const string& str){
		(*this) += str;
		return *this;
	}
	string& string::append(const string& str, size_t subpos, size_t sublen){
		insert(size(), str, subpos, sublen);
		return *this;
	}
	string& string::append(const char* s){
		(*this) += s;
		return *this;
	}
	string& string::append(const char* s, size_t n){
		insert(size(), s, n);
		return *this;
	}
	string& string::append(size_t n, char c){
		insert(end(), n, c);
		return *this;
	}
	template <class InputIterator>
	string& string::append(InputIterator first, InputIterator last){
		insert(end(), first, last);
		return *this;
	}
	string::iterator string::erase(iterator first, iterator last){
		size_t lengthOfMove = finish_ - last;
		for (auto i = 0; i != lengthOfMove; ++i){
			*(first + i) = *(last + i);
		}
		dataAllocator::destroy(first + lengthOfMove, finish_);
		finish_ = first + lengthOfMove;
		return first;
	}
	string& string::erase(size_t pos, size_t len){
		erase(begin() + pos, begin() + pos + len);
		return *this;
	}
	string::iterator string::erase(iterator p){
		return erase(p, end());
	}
	template <class InputIterator>
	string& string::replace(iterator i1, iterator i2,
		InputIterator first, InputIterator last){
		auto ptr = erase(i1, i2);
		insert(ptr, first, last);
		return *this;
	}
	string& string::replace(size_t pos, size_t len, const string& str){
		return replace(begin() + pos, begin() + pos + len, str.begin(), str.end());
	}
	string& string::replace(iterator i1, iterator i2, const string& str){
		return replace(i1, i2, str.begin(), str.end());
	}
	string& string::replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen){
		return replace(begin() + pos, begin() + pos + len, str.begin() + subpos, str.begin() + pos + sublen);
	}
	string& string::replace(size_t pos, size_t len, const char* s){
		return replace(begin() + pos, begin() + pos + len, s, s + strlen(s));
	}
	string& string::replace(iterator i1, iterator i2, const char* s){
		return replace(i1, i2, s, s + strlen(s));
	}
	string& string::replace(iterator i1, iterator i2, size_t n, char c){
		auto ptr = erase(i1, i2);
		insert(ptr, n, c);
		return *this;
	}
	string& string::replace(size_t pos, size_t len, const char* s, size_t n){
		return replace(begin() + pos, begin() + pos + len, s, s + n);
	}
	string& string::replace(iterator i1, iterator i2, const char* s, size_t n){
		return replace(i1, i2, s, s + n);
	}
	string& string::replace(size_t pos, size_t len, size_t n, char c){
		return replace(begin() + pos, begin() + pos + len, n, c);
	}
	/*size_t string::find(const char* s, size_t pos, size_t n) const{
		size_t lenghtOfS = strlen(s);
		if (n < lenghtOfS)
			return npos;
		int i, j;
		size_t res = 0;
		for (i = pos; i != pos + n; ++i){
			for (j = 0; j != lenghtOfS; ++j){
				if (*(begin() + i + j) != s[j])
					break;
			}
			if (j == lenghtOfS)
				return i;
		}
		return npos;
	}*/
	size_t string::find(const string& str, size_t pos) const{
		size_t lenghtOfS = str.size();
		if (size() - pos < lenghtOfS)
			return npos;
		int i, j;
		size_t res = 0;
		for (i = pos; i != size(); ++i){
			for (j = 0; j != lenghtOfS; ++j){
				if (*(begin() + i + j) != str[j])
					break;
			}
			if (j == lenghtOfS)
				return i;
		}
		return npos;
	}
	/*size_t string::find(const char* s, size_t pos) const;
	size_t string::find(char c, size_t pos) const;*/
}
#endif