#include "UFSetTest.h"

namespace TinySTL{
	namespace UFSetTest{
		void testCase1(){
			uf_set<10> uf;
			uf.Union(0, 1);
			uf.Union(2, 3);
			uf.Union(3, 1);
			assert(uf.Find(0) == uf.Find(2));
		}

		void testAllCases(){
			testCase1();
		}
	}
}