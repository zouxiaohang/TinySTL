#include "VectorTest.h"

namespace TinySTL{
	namespace VectorTest{

		void testCase1(){
			stdVec<std::string> v1(10, "zxh");
			tsVec<std::string> v2(10, "zxh");
			assert(TinySTL::Test::container_equal(v1, v2));

			stdVec<std::string> v3(10);
			tsVec<std::string> v4(10);
			assert(TinySTL::Test::container_equal(v3, v4));

			std::array<std::string, 3> arr = { "abc", "def", "ghi" };
			stdVec<std::string> v5(std::begin(arr), std::end(arr));
			tsVec<std::string> v6(std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(v5, v6));
		}
		void testCase2(){
			stdVec<int> temp1(10, 0);
			tsVec<int> temp2(10, 0);

			auto v1(temp1);
			auto v2(temp2);
			assert(TinySTL::Test::container_equal(v1, v2));

			auto v3(std::move(temp1));
			auto v4(std::move(temp2));
			assert(TinySTL::Test::container_equal(v3, v4));

			auto v5 = v1;
			auto v6 = v2;
			assert(TinySTL::Test::container_equal(v5, v6));

			auto v7 = std::move(v3);
			auto v8 = std::move(v4);
			assert(TinySTL::Test::container_equal(v7, v8));
		}
	}
}

using namespace TinySTL::VectorTest;
int main(){
	testCase1();
	testCase2();
	system("pause");
	return 0;
}