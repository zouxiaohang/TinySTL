#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <cstring>

namespace TinySTL{
	//********* [fill] ********************
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}
	inline void fill(char *first, char *last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}
	inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}
	//********* [fill_n] ********************
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
	template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}
	//************ [find] ****************
	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val){
		for (; first != last; ++first){
			if (*first == val)
				break;
		}
		return first;
	}
	//*********** [min] ********************
	template <class T> 
	const T& min(const T& a, const T& b){
		return !(b < a) ? a : b;
	}
	template <class T, class Compare>
	const T& min(const T& a, const T& b, Compare comp){
		return !comp(b, a) ? a : b;
	}
	//*********** [max] ********************
	template <class T> 
	const T& max(const T& a, const T& b){
		return (a < b) ? b : a;
	}
	template <class T, class Compare>
	const T& max(const T& a, const T& b, Compare comp){
		return (copm(a, b)) ? b : a;
	}
	//********** [make_heap] ***************
	template<class RandomAccessIterator, class Compare>
	static void up(RandomAccessIterator first, RandomAccessIterator last, Compare comp){//[first, last]
		if (first != last){
			auto range = last - first + 1;
			for (auto cur = last; rait > first; range /= 2){
				auto parent = first + (range / 2 - 1);
				if (comp(*parent, *cur))
					TinySTL::swap(*parent, *cur);
				cur = parent;
			}
		}
	}
	template<class RandomAccessIterator, class Compare>
	static void down(RandomAccessIterator first, RandomAccessIterator last, Compare comp){//[first, last]
		if (first != last){
			decltype(last - first) range = 1;
			for (auto cur = first; cur < last;range = cur - first + 1){
				auto child = first + (range * 2 - 1);//get the left child
				if (child <= last){
					if ((child + 1) <= last && *(child + 1) > *child)
						child = child + 1;//right child
					if (comp(*cur, *child))
						TinySTL::swap(*cur, *child);
					cur = child;
				}
				else 
					break;
			}
		}
	}
	template <class RandomAccessIterator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last){
		TinySTL::make_heap(first, last,
			typename TinySTL::less<TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
		const auto range = last - first;
		for (auto rait = first + range - 1; rait > first; --rait){
			down(first, rait, comp);
		}
	}
	//********* [push_heap] ***************
	template <class RandomAccessIterator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last);
	template <class RandomAccessIterator, class Compare>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
	//********* [pop_heap] ***************
	template <class RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last);
	template <class RandomAccessIterator, class Compare>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
	//********* [sort_heap] ***************
	template <class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last);
	template <class RandomAccessIterator, class Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
	//********* [is_heap] ***************
	template <class RandomAccessIterator>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last);
	template <class RandomAccessIterator, class Compare>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
}


#endif