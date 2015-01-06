#ifndef _STACK_TEST_H_
#define _STACK_TEST_H_

#include "TestUtil.h"

#include "../Stack.h"
#include <stack>

#include <cassert>
#include <string>

namespace TinySTL{
	namespace StackTest{
		template<class T>
		using stdSt = std::stack < T > ;
		template<class T>
		using tsSt = TinySTL::stack < T > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();

		void testAllCases();
	}
}

#endif