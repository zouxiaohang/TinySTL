#ifndef _LIST_TEST_H_
#define _LIST_TEST_H_

#include "TestUtil.h"

#include "../List.h"
#include <list>

#include <cassert>
#include <string>

namespace TinySTL{
	namespace ListTest{
		template<class T>
		using stdL = std::list < T > ;
		template<class T>
		using tsL = TinySTL::list < T > ;

		void testCase1();

		void testAllCases();
	}
}

#endif