#ifndef _UTILITY_H_
#define _UTILITY_H_

//#include "Algorithm.h"

namespace TinySTL{
	//************ [swap] ***************
	template<class T>
	void swap(T& a, T& b){
		T temp = a;
		a = b;
		b = temp;
	}
	//*********** [pair] ****************
	template<class T1, class T2>
	struct pair{
	public:
		typedef T1 first_type;
		typedef T2 second_type;
	public:
		T1 first;
		T2 second;
	public:
		pair(){}
		template<class U, class V> 
		pair(const pair<U, V>& pr);
		pair(const first_type& a, const second_type& b);
		pair& operator= (const pair& pr);
		void swap(pair& pr);
	public:
		template <class T1, class T2>
		friend bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
		template <class T1, class T2>
		friend bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
		template <class T1, class T2>
		friend bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
		template <class T1, class T2>
		friend bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
		template <class T1, class T2>
		friend bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
		template <class T1, class T2>
		friend bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
		template <class T1, class T2>
		friend void swap(pair<T1, T2>& x, pair<T1, T2>& y);
		
	};
	template<class T1, class T2>
	template<class U, class V>
	pair<T1, T2>::pair(const pair<U, V>& pr) :first(pr.first), second(pr.second){}
	template<class T1, class T2>
	pair<T1, T2>::pair(const first_type& a, const second_type& b) : first(a), second(b){}
	template<class T1, class T2>
	pair<T1, T2>& pair<T1, T2>::operator =(const pair<T1, T2>& pr){
		if (this != &pr){
			first = pr.first;
			second = pr.second;
		}
		return *this;
	}
	template<class T1, class T2>
	void pair<T1, T2>::swap(pair<T1, T2>& pr){
		TinySTL::swap(first, pr.first);
		TinySTL::swap(second, pr.second);
	}

	template <class T1, class T2>
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs){
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
	template <class T1, class T2>
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs){
		return !(lhs == rhs);
	}
	template <class T1, class T2>
	bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs){
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}
	template <class T1, class T2>
	bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs){
		return !(rhs<lhs);
	}
	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs){
		return rhs<lhs;
	}
	template <class T1, class T2>
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs){
		return !(lhs<rhs);
	}
	template <class T1, class T2>
	void swap(pair<T1, T2>& x, pair<T1, T2>& y){
		x.swap(y);
	}
	// ******* [make_pair] ************
	template<class U, class V>
	pair<U, V> make_pair(const U& u, const V& v){
		return pair<U, V>(u, v);
	}
}
#endif