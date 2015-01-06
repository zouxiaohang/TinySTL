#include "PriorityQueueTest.h"

namespace TinySTL{
	namespace PriorityQueueTest{
		void testCase1(){
			int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1, -2, -3 };
			stdPQ<int> pq1(std::begin(arr), std::end(arr));
			tsPQ<int> pq2(std::begin(arr), std::end(arr));
			
			while (!pq1.empty() && !pq2.empty()){
				assert(pq1.top() == pq2.top());
				pq1.pop(); pq2.pop();
			}
			assert(pq1.empty() && pq2.empty());
		}
		void testCase2(){
			tsPQ<std::string> pq;
			assert(pq.empty());

			pq.push("zxh");
			assert(!pq.empty());
		}
		void testCase3(){
			tsPQ<int> pq;
			auto i = 1;
			for (; i != 10; ++i){
				pq.push(i);
				assert(pq.size() == i);
			}
			for (i = pq.size(); i != 0; --i){
				pq.pop();
				assert(pq.size() == (i - 1));
			}
		}
		void testCase4(){
			stdPQ<int> pq1;
			tsPQ<int> pq2;

			pq1.push(30);
			pq1.push(100);
			pq1.push(25);
			pq1.push(40);

			pq2.push(30);
			pq2.push(100);
			pq2.push(25);
			pq2.push(40);

			while (!pq1.empty() && !pq2.empty()){
				assert(pq1.top() == pq2.top());
				pq1.pop(); 
				pq2.pop();
			}
		}
		void testCase5(){
			tsPQ<int> foo, bar;
			foo.push(15); foo.push(30); foo.push(10);
			bar.push(101); bar.push(202);

			assert(foo.size() == 3 && bar.size() == 2);
			foo.swap(bar);
			assert(foo.size() == 2 && bar.size() == 3);

			TinySTL::swap(foo, bar);
			assert(foo.size() == 3 && bar.size() == 2);
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