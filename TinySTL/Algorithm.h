#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <cstring>

namespace TinySTL{
	//********* [fill] ********************
	//********* [Algorithm Complexity: O(N)] ****************
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
	//********* [Algorithm Complexity: O(N)] ****************
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
	//********* [Algorithm Complexity: O(N)] ****************
	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val){
		for (; first != last; ++first){
			if (*first == val)
				break;
		}
		return first;
	}
	//*********** [min] ********************
	//********* [Algorithm Complexity: O(1)] ****************
	template <class T> 
	const T& min(const T& a, const T& b){
		return !(b < a) ? a : b;
	}
	template <class T, class Compare>
	const T& min(const T& a, const T& b, Compare comp){
		return !comp(b, a) ? a : b;
	}
	//*********** [max] ********************
	//********* [Algorithm Complexity: O(1)] ****************
	template <class T> 
	const T& max(const T& a, const T& b){
		return (a < b) ? b : a;
	}
	template <class T, class Compare>
	const T& max(const T& a, const T& b, Compare comp){
		return (copm(a, b)) ? b : a;
	}
	//********** [make_heap] ***************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class RandomAccessIterator, class Compare>
	//heap上溯算法
	static void up(RandomAccessIterator first, RandomAccessIterator last, 
		RandomAccessIterator head, Compare comp){//1.[first, last], 2.headr points the header of the heap
		if (first != last){
			int index = last - head;
			auto parentIndex = (index - 1) / 2;
			for (auto cur = last; parentIndex >= 0 && cur != head; parentIndex = (index - 1) / 2){
				auto parent = head + parentIndex;//get parent
				if (comp(*parent, *cur))
					TinySTL::swap(*parent, *cur);
				cur = parent;
				index = cur - head;
			}
		}
	}
	template<class RandomAccessIterator, class Compare>
	//heap下降算法
	static void down(RandomAccessIterator first, RandomAccessIterator last, 
		RandomAccessIterator head, Compare comp){//1.[first, last], 2.headr points the header of the heap
		if (first != last){
			auto index = first - head;
			auto leftChildIndex = index * 2 + 1;
			for (auto cur = first; leftChildIndex < (last - head + 1) && cur < last; leftChildIndex = index * 2 + 1){
				auto child = head + leftChildIndex;//get the left child
				if ((child + 1) <= last && *(child + 1) > *child)//cur has a right child
					child = child + 1;
				if (comp(*cur, *child))
					TinySTL::swap(*cur, *child);
				cur = child;
				index = cur - head;
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
		for (auto cur = first + range / 2 - 1; cur >= first; --cur){
			TinySTL::down(cur, last - 1, first, comp);
			if (cur == first) return;
		}
	}
	//********* [push_heap] ***************
	template <class RandomAccessIterator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last){
		TinySTL::push_heap(first, last,
			TinySTL::less<typename TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
		TinySTL::up(first, last - 1, first, comp);
	}
	//********* [pop_heap] ***************
	template <class RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last){
		TinySTL::pop_heap(first, last, 
			TinySTL::less<typename TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
		TinySTL::swap(*first, *(last - 1));
		if (last - first >= 2)
			TinySTL::down(first, last - 2, first, comp);
	}
	//********* [sort_heap] ***************
	template <class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last);
	template <class RandomAccessIterator, class Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
	//********* [is_heap] ***************
	template <class RandomAccessIterator>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last){
		return TinySTL::is_heap(first, last,
			TinySTL::less<typename TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
		const auto range = last - first;
		auto index = range / 2 - 1;
		for (auto cur = first + range / 2 - 1; cur >= first; --cur, --index){
			if (*(first + (index * 2 + 1)) > *cur ||//left child > cur
				((first + (index * 2 + 2)) <= last && *(first + (index * 2 + 2)) > *cur))//right child > cur
				return false;
			if (cur == first)
				break;
		}
		return true;
	}
}


#endif