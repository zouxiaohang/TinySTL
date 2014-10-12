#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Deque.h"
#include "Functional.h"
#include "Vector.h"

namespace TinySTL{
	//class of queue
	template<class T, class Containter = TinySTL::deque<T>>
	class queue{};
	//class of priority_queue
	template <class T, class Container = TinySTL::vector<T>, 
				class Compare = TinySTL::less<typename Container::value_type>> 
	class priority_queue{};
}

#endif