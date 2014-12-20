#ifndef _ALGORITHM_TEST_H_
#define _ALGORITHM_TEST_H_

#include "TestUtil.h"

#include "../Algorithm.h"
#include <algorithm>

#include <cassert>
#include <vector>

namespace TinySTL{
	namespace AlgorithmTest{
		void testFill();
		void testFillN();
		void testMinMax();
		void testHeapAlgorithm();
		void testIsHeap();
	}
}

#endif