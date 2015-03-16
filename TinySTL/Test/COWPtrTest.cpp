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

			*cp1 = "zouxiaohang";
			assert(*cp1 == "zouxiaohang");
			assert(*cp2 == "hello" && *cp3 == "hello");

			cow_ptr<string> cp4;
			assert(cp4 == nullptr);
		}
		void testCase2(){
			cow_ptr<string> cp1(new string("zouxiaohang"));
			auto cp2 = cp1, cp3 = cp1;
			assert(cp1 == cp2 && cp2 == cp3);
			assert(*cp1 == *cp2 && *cp2 == *cp3 && *cp3 == "zouxiaohang");

			*cp2;//read
			assert(cp1 == cp2 && cp2 == cp3);
			assert(*cp1 == *cp2 && *cp2 == *cp3 && *cp3 == "zouxiaohang");

			cp2->append(" C++");//write
			assert(*cp1 == *cp3 && *cp3 == "zouxiaohang");
			assert(*cp2 == "zouxiaohang C++");
		}

		void testAllCases(){
			testCase1();
			testCase2();
		}
	}
}