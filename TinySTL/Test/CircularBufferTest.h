#ifndef _CIRCULAR_BUFFER_TEST_H_
#define _CIRCULAR_BUFFER_TEST_H_

#include "TestUtil.h"

#include "../CircularBuffer.h"

#include <cassert>
#include <string>
#include <iostream>

namespace TinySTL{
	namespace CircularBufferTest{
		template<class T, size_t N>
		using tsCB = TinySTL::circular_buffer<T, N>;

		template<class T, size_t N>
		bool circular_buffer_equal(tsCB<T, N>& cb1, tsCB<T, N> cb2){
			auto it1 = cb1.first(), it2 = cb2.first();
			for (; it1 != cb1.last() && it2 != cb1.last(); ++it1, ++it2){
				if (*it1 != *it2)
					return false;
			}
			return (it1 == cb1.last() && it2 == cb2.last() && (*(cb1.last()) == *(cb2.last())));
		}

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();
		void testCase6();

		void testAllCases();
	}
}

#endif