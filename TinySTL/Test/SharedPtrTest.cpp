#include "SharedPtrTest.h"

#include "../String.h"

namespace TinySTL{
	namespace SharedPtrTest{
		void testCase1(){
			shared_ptr<int> sp1(new int(10));
			assert(*(sp1.get()) == 10);
			
			shared_ptr<int> sp2(new int(1), default_delete<int>());
			assert(sp2.use_count() == 1);

			auto sp3(sp2);
			assert(sp3.use_count() == 2);
			{
				auto sp4 = sp2;
				assert(sp4.use_count() == 3 && sp3.use_count() == sp4.use_count());

				assert(sp2.get() == sp3.get() && sp2.get() == sp4.get());
				assert(sp2 == sp3 && !(sp2 != sp4));
			}
			assert(sp3.use_count() == 2);

			shared_ptr<string> sp5(new string("hello"));
			assert(*sp5 == "hello");
			sp5->append(" world");
			assert(*sp5 == "hello world");

			auto sp6 = make_shared<string>(10, '0');
			assert(*sp6 == "0000000000");

			shared_ptr<int> spp;
			assert(spp == nullptr);
			assert(!(spp != nullptr));
		}

		void testAllCases(){
			testCase1();
		}
	}
}