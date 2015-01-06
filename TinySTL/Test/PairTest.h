#ifndef _PAIR_TEST_H_
#define _PAIR_TEST_H_

#include "TestUtil.h"

#include "../Utility.h"
#include <utility>

#include <cassert>
#include <iostream>
#include <string>

namespace TinySTL{
	namespace PairTest{
		template<typename T>
		using stdPair = std::pair < T, T > ;
		template<typename T>
		using tsPair = TinySTL::pair < T, T > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();

		void testAllCases();
	}
}
#endif