#include <iostream>

#include "Algorithm.h"
#include "Profiler\Profiler.h"

#include "Test\AlgorithmTest.h"
#include "Test\AVLTreeTest.h"
#include "Test\BitmapTest.h"
#include "Test\BinarySearchTreeTest.h"
#include "Test\CircularBufferTest.h"
#include "Test\COWPtrTest.h"
#include "Test\DequeTest.h"
#include "Test\GraphTest.h"
#include "Test\ListTest.h"
#include "Test\PairTest.h"
#include "Test\PriorityQueueTest.h"
#include "Test\QueueTest.h"
#include "Test\RefTest.h"
#include "Test\SharedPtrTest.h"
#include "Test\StackTest.h"
#include "Test\StringTest.h"
#include "Test\SuffixArrayTest.h"
#include "Test\TrieTreeTest.h"
#include "Test\TypeTraitsTest.h"
#include "Test\UFSetTest.h"
#include "Test\UniquePtrTest.h"
#include "Test\Unordered_setTest.h"
#include "Test\VectorTest.h"

using namespace TinySTL::Profiler;

int main(){
	TinySTL::AlgorithmTest::testAllCases();
	TinySTL::AVLTreeTest::testAllCases();
	TinySTL::BitmapTest::testAllCases();
	TinySTL::BinarySearchTreeTest::testAllCases();
	TinySTL::CircularBufferTest::testAllCases();
	TinySTL::COWPtrTest::testAllCases();
	TinySTL::DequeTest::testAllCases();
	TinySTL::ListTest::testAllCases();
	TinySTL::GraphTest::testAllCases();
	TinySTL::PairTest::testAllCases();
	TinySTL::PriorityQueueTest::testAllCases();
	TinySTL::QueueTest::testAllCases();
	TinySTL::RefTest::testAllCases();
	TinySTL::SharedPtrTest::testAllCases();
	TinySTL::StackTest::testAllCases();
	TinySTL::StringTest::testAllCases();
	TinySTL::SuffixArrayTest::testAllCases();
	TinySTL::TrieTreeTest::testAllCases();
	TinySTL::TypeTraitsTest::testAllCases();
	TinySTL::UFSetTest::testAllCases();
	TinySTL::UniquePtrTest::testAllCases();
	TinySTL::Unordered_setTest::testAllCases();
	TinySTL::VectorTest::testAllCases();
	 
	system("pause");
	return 0;
}