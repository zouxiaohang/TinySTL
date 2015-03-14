#include "PairTest.h"

namespace TinySTL{
	namespace PairTest{
		template<class Container1, class Container2>
		static inline bool container_equal(const Container1& pair1, const Container2& pair2){
			return (pair1.first == pair2.first && pair1.second == pair2.second);
		}
		void testCase1(){
			stdPair<int> p1(5, 5);
			tsPair<int> p2(5, 5);
			assert(container_equal(p1, p2));
		}
		void testCase2(){
			stdPair<int> p1(stdPair<int>(0, 0));
			tsPair<int> p2(tsPair<int>(0, 0));
			assert(container_equal(p1, p2));
		}
		void testCase3(){
			stdPair<std::string> temp1 = std::make_pair(std::string("zxh"), std::string("zxh"));
			stdPair<std::string> p1 = temp1;
		
			tsPair<std::string> temp2 = TinySTL::make_pair(std::string("zxh"), std::string("zxh"));
			tsPair<std::string> p2 = temp2;
		
			assert(container_equal(p1, p2));
		}
		void testCase4(){
			TinySTL::pair<int, char> foo(10, 'z');
			TinySTL::pair<int, char> bar(90, 'a');
		
			assert(!(foo == bar));
			assert(foo != bar);
			assert(foo < bar);
			assert(!(foo > bar));
			assert(foo <= bar);
			assert(!(foo >= bar));
		}
		void testCase5(){
			TinySTL::pair<int, char> foo(10, 'z');
			TinySTL::pair<int, char> bar(90, 'a');
		
			foo.swap(bar);
		
			assert(foo.first == 90 && foo.second == 'a');
			assert(bar.first == 10 && bar.second == 'z');
		}


		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
			testCase4();
			testCase5();
		}
	}
}