#ifndef _STRING_TEST_H_
#define _STRING_TEST_H_

#include "TestUtil.h"

#include "../String.h"
#include <string>

#include <cassert>
#include <iterator>

namespace TinySTL{
	namespace StringTest{
		using stdStr = std::string;
		using tsStr = TinySTL::string;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();
		void testCase6();
		void testCase7();
		void testCase8();
	}
}

#endif