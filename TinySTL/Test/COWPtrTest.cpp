#include "COWPtrTest.h"

#include "../String.h"

namespace TinySTL{
	namespace COWPtrTest{
		void testCase1(){
			cow_ptr<string> cp1(new string("hello"));
			assert(*cp1 == "hello");
			assert(cp1);
			
			auto cp2 = cp1;
			assert(*cp2 == "hello");

			cow_ptr<string> cp3;
			cp3 = cp1;
			assert(*cp3 == "hello");

			assert(cp1.get() == cp2.get() && cp2.get() == cp3.get());

			assert(cp1 == cp2 && !(cp2 != cp3));

			cow_ptr<string> cp4;
			assert(cp4 == nullptr);
		}

		void testAllCases(){
			testCase1();
		}
	}
}