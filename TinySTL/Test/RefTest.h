#ifndef _REF_TEST_H_
#define _REF_TEST_H_

#include "../Detail/Ref.h"

#include <cassert>

namespace TinySTL{
	namespace RefTest{
		template<class T>
		using ref_t = TinySTL::Detail::ref_t < T > ;

		void testCaseRef();
		void testAllCases();
	}
}

#endif