#include "SuffixArrayTest.h"

namespace TinySTL{
	namespace SuffixArrayTest{
		void testCase1(){
			char arr[] = { 'a', 'a', 'b', 'a', 'a', 'a', 'a', 'b' };

			TinySTL::suffix_array sa(arr, 8);
			auto v = sa.suffixArray();
			auto t = std::vector<int> {3, 4, 5, 0, 6, 1, 7, 2};
			assert(TinySTL::Test::container_equal(v, t));
		}
	}
}

using namespace TinySTL::SuffixArrayTest;
int main(){
	testCase1();
	system("pause");
	return 0;
}