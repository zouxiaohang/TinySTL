#ifndef _AVL_TREE_TEST_H_
#define _AVL_TREE_TEST_H_

#include "TestUtil.h"

#include "../AVLTree.h"

#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <vector>

namespace TinySTL{
	namespace AVLTreeTest{
		template<class T>
		using tsAVL = TinySTL::avl_tree < T > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();


		void testAllCases();
	}
}

#endif