#include "COWPtrTest.h"

#include "../String.h"

namespace TinySTL{
	namespace COWPtrTest{
		void testCase1(){
			cow_ptr<string> cp1(new string("hello"));
			assert(*cp1 == "hello");
			
			cp1->append(" world");
			auto cp2 = cp1;
			assert(*cp2 == "hello world");

			cow_ptr<string> cp3;
			cp3 = cp1;
			assert(*cp3 == "hello world");
		}

		void testAllCases(){
			testCase1();
		}
	}
}