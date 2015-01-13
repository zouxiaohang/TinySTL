#ifndef _LIST_TEST_H_
#define _LIST_TEST_H_

#include "TestUtil.h"

#include "../List.h"
#include <list>

#include <cassert>
#include <functional>
#include <string>
#include <random>

namespace TinySTL{
	namespace ListTest{
		template<class T>
		using stdL = std::list < T > ;
		template<class T>
		using tsL = TinySTL::list < T > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();
		void testCase6();
		void testCase7();
		void testCase8();
		void testCase9();
		void testCase10();
		void testCase11();
		void testCase12();
		void testCase13();
		void testCase14();
		void testCase15();

		void testAllCases();
	}
}

#endif