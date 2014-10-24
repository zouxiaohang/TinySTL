#include <algorithm>
#include <atomic>
#include <cassert>
#include <cctype>
#include <condition_variable>
#include <iostream>
#include <list>
#include <new>
#include <mutex>
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include <random>
#include <thread>
#include <utility>

#include <boost\circular_buffer.hpp>

#include "Algorithm.h"
#include "String.h"
#include "Vector.h"
#include "Profiler\Profiler.h"

#include "BinarySearchTree.h"
#include "CircularBuffer.h"
#include "Deque.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;
using namespace TinySTL::Profiler;
bool comp_case_insensitive(char c1, char c2) {
	return (std::tolower(c1) == std::tolower(c2));
}
int main(){
	TinySTL::deque<int> dq;
	for (int i = 0; i != 10; ++i)
		dq.push_front(i);
	/*for (auto x : dq)
		cout << x << endl;*/
	for (auto rit = dq.begin(); rit != dq.end(); ++rit)
		cout << *rit << endl;
	for (auto x : dq)
		cout << x << endl;
	system("pause");
	return 0;
}
