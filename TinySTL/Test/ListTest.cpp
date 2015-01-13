#include "ListTest.h"

namespace TinySTL{
	namespace ListTest{
		void testCase1(){
			stdL<int> l1(10, 0);
			tsL<int> l2(10, 0);
			assert(TinySTL::Test::container_equal(l1, l2));

			int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			stdL<int> l3(std::begin(arr), std::end(arr));
			tsL<int> l4(std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(l3, l4));

			auto l5(l1);
			auto l6(l2);
			assert(TinySTL::Test::container_equal(l5, l6));

			auto l7 = l1;
			auto l8 = l2;
			assert(TinySTL::Test::container_equal(l7, l8));
		}
		void testCase2(){
			tsL<std::string> l1;
			assert(l1.empty());
			assert(l1.size() == 0);

			std::string arr[] = { "1", "2", "3" };
			tsL<std::string> l2(std::begin(arr), std::end(arr));
			assert(!l2.empty());
			assert(l2.size() == 3);
		}
		void testCase3(){
			std::string arr[] = { "1", "2", "3" };
			tsL<std::string> l(std::begin(arr), std::end(arr));
			assert(l.back() == arr[2]);
			assert(l.front() == arr[0]);

			l.front() = "front";
			l.back() = "back";
			assert(l.back() == "back");
			assert(l.front() == "front");
		}
		void testCase4(){
			stdL<int> l1;
			tsL<int> l2;
			for (auto i = 0; i != 10; ++i){
				l1.push_front(i);
				l2.push_front(i);
			}
			assert(TinySTL::Test::container_equal(l1, l2));
			for (auto i = 0; i != 10; ++i){
				l1.push_back(i);
				l2.push_back(i);
			}
			assert(TinySTL::Test::container_equal(l1, l2));
			for (auto i = 0; i != 5; ++i){
				l1.pop_back();
				l2.pop_back();
			}
			assert(TinySTL::Test::container_equal(l1, l2));
			for (auto i = 0; i != 5; ++i){
				l1.pop_front();
				l2.pop_front();
			}
			assert(TinySTL::Test::container_equal(l1, l2));
		}
		void testCase5(){
			stdL<int> l1;
			tsL<int> l2;

			for (auto i = 0; i != 10; ++i){
				l1.push_back(i);
				l2.push_back(i);
			}
			auto rit1 = l1.rbegin();
			auto rit2 = l2.rbegin();
			for (; rit1 != l1.rend() && rit2 != l2.rend(); ++rit1, ++rit2){
				assert(*rit1 == *rit2);
			}
			assert(rit1 == l1.rend() && rit2 == l2.rend());
		}
		void testCase6(){
			stdL<int> l1;
			tsL<int> l2;

			l1.insert(l1.end(), 10, -1);
			l2.insert(l2.end(), 10, -1);
			assert(TinySTL::Test::container_equal(l1, l2));

			auto it1 = l1.begin();
			auto it2 = l2.begin();
			for (auto i = l1.size() / 2 + 1; i != 0; --i){
				++it1;
				++it2;
			}
			l1.insert(it1, 1);
			l2.insert(it2, 1);
			assert(TinySTL::Test::container_equal(l1, l2));

			int arr[] = { 1, 2, 3, 4, 5 };
			it1 = l1.end();
			it2 = l2.end();
			l1.insert(it1, std::begin(arr), std::end(arr));
			l2.insert(it2, std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(l1, l2));
		}
		void testCase7(){
			stdL<int> l1;
			tsL<int> l2;
			for (auto i = 0; i != 100; ++i){
				l1.push_back(i);
				l2.push_back(i);
			}

			l1.erase(l1.begin()); l1.erase(--l1.end());
			l2.erase(l2.begin()); l2.erase(--l2.end());
			assert(TinySTL::Test::container_equal(l1, l2));

			l1.erase(l1.begin(), l1.end());
			l2.erase(l2.begin(), l2.end());
			assert(TinySTL::Test::container_equal(l1, l2));
		}
		void testCase8(){
			tsL<int> l1, l2;
			l1.push_back(1); l1.push_back(1); l1.push_back(1);
			l2.push_back(2); l2.push_back(2);

			l1.swap(l2);
			assert(l1.size() == 2 && l2.size() == 3);
			TinySTL::swap(l1, l2);
			assert(l1.size() == 3 && l2.size() == 2);
		}
		void testCase9(){
			std::random_device rd;
			stdL<int> l1;
			tsL<int> l2;
			for (auto i = 0; i != 100; ++i){
				auto ret = rd() % 65536;
				l1.push_back(ret);
				l2.push_back(ret);
			}
			
			l1.sort();
			l2.sort();
			assert(TinySTL::Test::container_equal(l1, l2));

			l1.sort(std::greater<int>());
			l2.sort(std::greater<int>());
			assert(TinySTL::Test::container_equal(l1, l2));
		}
		void testCase10(){
			int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			stdL<int> l1(std::begin(arr), std::end(arr));
			tsL<int> l2(std::begin(arr), std::end(arr));

			l1.reverse();
			l2.reverse();
			assert(TinySTL::Test::container_equal(l1, l2));
		}
		void testCase11(){
			int arr1[] = { 0, 1, 3, 5, 9 }, arr2[] = { 2, 4, 6, 7, 8 };
			stdL<double> first1(std::begin(arr1), std::end(arr1)), second1(std::begin(arr2), std::end(arr2));
			tsL<double> first2(std::begin(arr1), std::end(arr1)), second2(std::begin(arr2), std::end(arr2));

			first1.merge(second1);
			first2.merge(second2);
			assert(TinySTL::Test::container_equal(first1, first2));
		}
		void testCase12(){
			int arr[] = { 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8, 8, 9, 11 };
			stdL<int> l1(std::begin(arr), std::end(arr));
			tsL<int> l2(std::begin(arr), std::end(arr));

			l1.unique();
			l2.unique();
			assert(TinySTL::Test::container_equal(l1, l2));
		}
		void testCase13(){
			int arr[] = { 17, 89, 7, 14, 89, 0, 1, 4 };
			stdL<int> l1(std::begin(arr), std::end(arr));
			tsL<int> l2(std::begin(arr), std::end(arr));

			l1.remove(89);
			l2.remove(89);
			assert(TinySTL::Test::container_equal(l1, l2));

			auto func = [](int n){return n % 2 == 0; };
			l1.remove_if(func);
			l2.remove_if(func);
			assert(TinySTL::Test::container_equal(l1, l2));
		}
		void testCase14(){
			stdL<int> l1(10, 0), l3(10, 1);
			tsL<int> l2(10, 0), l4(10, 1);

			l1.splice(l1.begin(), l3);
			l2.splice(l2.begin(), l4);
			assert(TinySTL::Test::container_equal(l1, l2));

			auto l5 = l1;
			auto l6 = l2;
			l1.splice(l1.end(), l5, l5.begin());
			l2.splice(l2.end(), l6, l6.begin());
			assert(TinySTL::Test::container_equal(l1, l2));

			auto it1 = l1.begin();
			auto it2 = l2.begin();
			for (auto i = 0; i != l1.size() / 2; ++i){
				++it1;
				++it2;
			}
			l1.splice(it1, l5, l5.begin(), l5.end());
			l2.splice(it2, l6, l6.begin(), l6.end());
			assert(TinySTL::Test::container_equal(l1, l2));
		}
		void testCase15(){
			tsL<int> l1(10, 0), l2(10, 1), l3(10, 0);

			assert(l1 == l3);
			assert(l1 != l2);
		}


		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
			testCase4();
			testCase5();
			testCase6();
			testCase7();
			testCase8();
			testCase9();
			testCase10();
			testCase11();
			testCase12();
			testCase13();
			testCase14();
			testCase15();
		}
	}
}