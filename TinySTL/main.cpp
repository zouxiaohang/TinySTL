//#include <algorithm>
//#include <atomic>
//#include <cassert>
//#include <cctype>
//#include <condition_variable>
//#include <iostream>
//#include <list>
//#include <new>
//#include <mutex>
//#include <memory>
//#include <string>
//#include <vector>
//#include <iterator>
//#include <queue>
//#include <random>
//#include <thread>
//#include <utility>
//
//#include <boost\circular_buffer.hpp>
//
//#include "Algorithm.h"
//#include "String.h"
//#include "Vector.h"
//#include "Profiler\Profiler.h"
//
//#include "AVLTree.h"
//#include "BinarySearchTree.h"
//#include "CircularBuffer.h"
//#include "Deque.h"
//#include "Queue.h"
//#include "Stack.h"
//
//using namespace std;
//using namespace TinySTL::Profiler;
//bool mypredicate(int i, int j) {
//	return (i == j);
//}
////int main(){
////	TinySTL::vector<int> myvector;
////	for (int i = 1; i<6; i++) myvector.push_back(i * 10); // myvector: 10 20 30 40 50
////
////	int myints[] = { 10, 20, 80, 320, 1024 };                //   myints: 10 20 80 320 1024
////
////	std::pair<TinySTL::vector<int>::iterator, int*> mypair;
////
////	// using default comparison:
////	mypair = TinySTL::mismatch(myvector.begin(), myvector.end(), myints);
////	std::cout << "First mismatching elements: " << *mypair.first;
////	std::cout << " and " << *mypair.second << '\n';
////
////	++mypair.first; ++mypair.second;
////
////	// using predicate comparison:
////	mypair = TinySTL::mismatch(mypair.first, myvector.end(), mypair.second, mypredicate);
////	std::cout << "Second mismatching elements: " << *mypair.first;
////	std::cout << " and " << *mypair.second << '\n';
////	system("pause");
////	return 0;
////}
