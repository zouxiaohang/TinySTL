#ifndef _ALGORITHM_TEST_H_
#define _ALGORITHM_TEST_H_

#include "TestUtil.h"

#include "../Algorithm.h"
#include <algorithm>

#include <array>
#include <cctype>
#include <cstring>
#include <cassert>
#include <functional>
#include <list>
#include <random>
#include <vector>

#include "../BinarySearchTree.h"
#include "../List.h"
#include "../Vector.h"


namespace TinySTL{
	namespace AlgorithmTest{
		void testFill();
		void testFillN();
		void testMinMax();
		void testHeapAlgorithm();
		void testIsHeap();
		void testAllOf();
		void testNoneOf();
		void testAnyOf();
		void testForEach();
		void testFind();
		void testFindEnd();
		void testFindFirstOf();
		void testAdjacentFind();
		void testCount();
		void testMismatch();
		void testEqual();
		void testIsPermutation();
		void testSearch();
		void testAdvance();
		void testSort();
		void testGenerate();
		void testDistance();
		void testCopy();

		void testAllCases();
	}
}

#endif