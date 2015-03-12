#include "UniquePtrTest.h"

#include "../String.h"

namespace {
	template<class T>
	struct Del{
		void operator()(T *p){ delete p; }
	};
}

namespace TinySTL{
	namespace UniquePtrTest{
		void testCase1(){
			unique_ptr<int> up1;
			assert(up1 == nullptr);

			unique_ptr<int> up2(new int(5));
			assert(up2 != nullptr);
			assert(*up2 == 5);

			unique_ptr<string, Del<string>> up3(new string("zouxiaohang"), Del<string>());
			assert(up3 != nullptr);
			assert(*up3 == "zouxiaohang");

			auto up4(std::move(up2));
			assert(*up4 == 5);
			assert(up2 == nullptr);

			unique_ptr<string, Del<string>> up5;
			up5 = std::move(up3);
			assert(*up5 == "zouxiaohang");
			assert(up3 == nullptr);

			auto up6 = make_unique<string>(6, 'z');
			assert(*up6 == "zzzzzz");
		}
		void testCase2(){
			auto up = make_unique<string>(10, '0');
			up->append("111");
			assert(*up == "0000000000111");

			up.release();
			assert(up == nullptr);

			up.reset(new string("hello"));
			assert(*up == "hello");
		}
		void testCase3(){
			auto up1 = make_unique<string>(2, '0');
			auto up2 = make_unique<string>(2, '1');

			up1.swap(up2);
			assert(*up1 == "11" && *up2 == "00");

			swap(up1, up2);
			assert(*up1 == "00" && *up2 == "11");
		}

		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
		}
	}
}