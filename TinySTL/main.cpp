#include <iostream>

#include "Algorithm.h"
#include "Profiler\Profiler.h"

#include "Test\AlgorithmTest.h"
#include "Test\BitmapTest.h"
#include "Test\CircularBufferTest.h"
#include "Test\DequeTest.h"
#include "Test\PairTest.h"
#include "Test\PriorityQueueTest.h"
#include "Test\QueueTest.h"
#include "Test\StackTest.h"
#include "Test\StringTest.h"
#include "Test\SuffixArrayTest.h"
#include "Test\VectorTest.h"

using namespace std;
using namespace TinySTL::Profiler;

int main(){
	TinySTL::AlgorithmTest::testAllCases();
	TinySTL::BitmapTest::testAllCases();
	TinySTL::CircularBufferTest::testAllCases();
	TinySTL::DequeTest::testAllCases();
	TinySTL::PairTest::testAllCases();
	TinySTL::PriorityQueueTest::testAllCases();
	TinySTL::QueueTest::testAllCases();
	TinySTL::StackTest::testAllCases();
	TinySTL::StringTest::testAllCases();
	TinySTL::SuffixArrayTest::testAllCases();
	TinySTL::VectorTest::testAllCases();

	system("pause");
	return 0;
}