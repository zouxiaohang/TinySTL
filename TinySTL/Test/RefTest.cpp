#include "RefTest.h"

namespace TinySTL{
	namespace RefTest{
		void testCaseRef(){
			ref_t<int> r1;
			assert(r1.count() == 0);
			assert(r1.get_data() == nullptr);

			int n = 0;
			ref_t<int> r2(&n);
			assert(r2.count() == 1);
			assert(r2.get_data() != nullptr);

			++r2;
			assert(r2.count() == 2);

			--r2;
			assert(r2.count() == 1);
		}

		void testAllCases(){
			testCaseRef();
		}
	}
}