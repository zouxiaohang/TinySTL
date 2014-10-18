#include <algorithm>
#include <atomic>
#include <cassert>
#include <condition_variable>
#include <iostream>
#include <list>
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

int main(){
	//TinySTL::deque<int> dq;
	//int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	int array[] = { 5, 3, 2, 7, 6, 8, 8 };
	TinySTL::binary_search_tree<int> bst;
	bst.insert(array, array + 7);
	//std::vector<int> vec;
	TinySTL::vector<int> vec;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 1000000; ++i){
		vec.push_back(i);
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
	cout << ProfilerInstance::millisecond() << endl;

	system("pause");
	return 0;
}
