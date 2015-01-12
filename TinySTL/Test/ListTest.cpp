#include "ListTest.h"

namespace TinySTL{
	namespace ListTest{
		void testCase1(){
			stdL<int> l1(10, 0);
			tsL<int> l2(10, 0);
			assert(TinySTL::Test::container_equal(l1, l2));

			int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			stdL<int> l3(std::begin(arr), std::end(arr));
			tsL<int> l4(std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(l3, l4));

			auto l5(l1);
			auto l6(l2);
			assert(TinySTL::Test::container_equal(l5, l6));

			auto l7 = l1;
			auto l8 = l2;
			assert(TinySTL::Test::container_equal(l7, l8));
		}


		void testAllCases(){
			testCase1();
		}
	}
}