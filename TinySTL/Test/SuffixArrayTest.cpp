#include "SuffixArrayTest.h"

namespace TinySTL{
	namespace SuffixArrayTest{
		void testCase(){
			//char arr[] = { 'a', 'a', 'b', 'a', 'a', 'a', 'a', 'b' };
			std::string str("aabaaaab");

			//TinySTL::suffix_array sa(arr, 8);
			TinySTL::suffix_array sa(str.data(), str.size());
			auto sa1 = sa.suffixArray();
			auto sa2 = TinySTL::suffix_array::array_type{3, 4, 5, 0, 6, 1, 7, 2};
			assert(TinySTL::Test::container_equal(sa1, sa2));

			auto ra1 = sa.rankArray();
			auto ra2 = TinySTL::suffix_array::array_type{ 3, 5, 7, 0, 1, 2, 4, 6 };
			assert(TinySTL::Test::container_equal(ra1, ra2));

			auto ha1 = sa.heightArray();
			auto ha2 = TinySTL::suffix_array::array_type{ 3, 2, 3, 1, 2, 0, 1 };
			assert(TinySTL::Test::container_equal(ha1, ha2));
		}

		
		void testAllCases(){
			testCase();
		}
	}
}