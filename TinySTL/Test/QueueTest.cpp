#include "QueueTest.h"

namespace TinySTL{
	namespace QueueTest{
		void testCase1(){
			stdQ<int> q1;
			tsQ<int> q2;

			for (auto i = 0; i != 10; ++i){
				q1.push(i);
				q2.push(i);
			}
			for (auto i = 0; i != 10; ++i){
				assert(q1.front() == q2.front());
				q1.pop();
				q2.pop();
			}
		}
		void testCase2(){
			tsQ<int> q1;
			for (auto i = 0; i != 10; ++i)
				q1.push(i);
			auto q2(q1);
			assert(q1 == q2);
			assert(!(q1 != q2));
		}
		void testCase3(){
			tsQ<int> q;
			assert(q.empty());
			assert(q.size() == 0);
			
			q.push(10);
			q.push(11);
			assert(!q.empty());
			assert(q.size() == 2);
		}
		void testCase4(){
			tsQ<std::string> q;
			q.push("front");
			q.push("back");
			
			assert(q.front() == "front");
			assert(q.back() == "back");
		}
		void testCase5(){
			tsQ<int> q1, q2;

			q1.push(1); q1.push(2); q1.push(3);
			q2.push(1); q2.push(2);

			assert(q1.size() == 3 && q2.size() == 2);
			q1.swap(q2);
			assert(q1.size() == 2 && q2.size() == 3);
			TinySTL::swap(q1, q2);
			assert(q1.size() == 3 && q2.size() == 2);
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