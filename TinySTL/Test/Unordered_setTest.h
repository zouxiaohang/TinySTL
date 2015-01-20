#ifndef _UNORDERED_SET_TEST_H_
#define _UNORDERED_SET_TEST_H_

#include "TestUtil.h"

#include "../Unordered_set.h"
#include <unordered_set>

#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <vector>

namespace TinySTL{
	namespace Unordered_setTest{
		template<class T>
		using stdUst = std::unordered_set < T > ;
		template<class T>
		using tsUst = TinySTL::Unordered_set < T > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();

		void testAllCases();
	}
}

#endif