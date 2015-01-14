#ifndef _BINARY_SEARCH_TREE_TEST_H_
#define _BINARY_SEARCH_TREE_TEST_H_

#include "TestUtil.h"

#include "../BinarySearchTree.h"

#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <vector>

namespace TinySTL{
	namespace BinarySearchTreeTest{
		template<class T>
		using tsBst = TinySTL::binary_search_tree < T > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();

		void testAllCases();
	}
}

#endif