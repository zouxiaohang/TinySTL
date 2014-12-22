#ifndef _VECTOR_TEST_H_
#define _VECTOR_TEST_H_

#include "../Vector.h"
#include "TestUtil.h"

#include <vector>

#include <array>
#include <cassert>
#include<iostream>
#include <iterator>
#include <string>

template<class T>
using stdVec = std::vector < T > ;

template<class T>
using tsVec = TinySTL::vector < T > ;

namespace TinySTL{
	namespace VectorTest{
		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();
	}
}

#endif