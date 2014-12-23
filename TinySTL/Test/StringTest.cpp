#include "StringTest.h"

namespace TinySTL{
	namespace StringTest{

		void testCase1(){
			const char *ptr = "hello world";

			stdStr s1(ptr);
			tsStr s2(ptr);
			assert(TinySTL::Test::container_equal(s1, s2));

			stdStr s3(ptr, 5);
			tsStr s4(ptr, 5);
			assert(TinySTL::Test::container_equal(s3, s4));

			stdStr s5(10, 'z');
			tsStr s6(10, 'z');
			assert(TinySTL::Test::container_equal(s5, s6));

			char arr[] = "zouxiaohang love cpp";
			stdStr s7(std::begin(arr), std::end(arr));
			tsStr s8(std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(s7, s8));
		}
		void testCase2(){
			stdStr temp1("hello, world");
			tsStr temp2("hello, world");

			stdStr s1(temp1);
			tsStr s2(temp2);
			assert(TinySTL::Test::container_equal(s1, s2));

			stdStr s3(std::move(s1));
			tsStr s4(std::move(s2));
			assert(TinySTL::Test::container_equal(s3, s4));

			stdStr s5(temp1, 1);
			tsStr s6(temp2, 1);
			assert(TinySTL::Test::container_equal(s5, s6));

			stdStr s7(temp1, 0, 5);
			tsStr s8(temp2, 0, 5);
			assert(TinySTL::Test::container_equal(s7, s8));
		}
		void testCase3(){
			stdStr t1("hello, world");
			tsStr t2("hello, world");

			stdStr s1; s1 = 'a';
			tsStr s2; s2 = 'a';
			assert(TinySTL::Test::container_equal(s1, s2));

			stdStr s3; s3 = "hello";
			tsStr s4; s4 = "hello";
			assert(TinySTL::Test::container_equal(s3, s4));

			stdStr s5; s5 = t1;
			tsStr s6; s6 = t2;
			assert(TinySTL::Test::container_equal(s5, s6));

			stdStr s7; s7 = std::move(t1);
			tsStr s8; s8 = std::move(t2);
			assert(TinySTL::Test::container_equal(s7, s8));
		}
		void testCase4(){
			tsStr str("Test string");
			for (tsStr::iterator it = str.begin(); it != str.end(); ++it)
				std::cout << *it;
			std::cout << '\n';
			for (tsStr::reverse_iterator it = str.rbegin(); it != str.rend(); ++it)
				std::cout << *it;
			std::cout << '\n';
		}
	}
}

using namespace TinySTL::StringTest;
int main(){
	testCase1();
	testCase2();
	testCase3();
	testCase4();
	system("pause");
	return 0;
}