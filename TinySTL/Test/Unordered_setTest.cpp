#include "Unordered_setTest.h"

namespace TinySTL{
	namespace Unordered_setTest{
		template<class Container1, class Container2>
		bool container_equal(Container1& con1, Container2& con2){
			std::vector<typename Container1::value_type> vec1, vec2;
			for (auto& item : con1){
				vec1.push_back(item);
			}
			for (auto& item : con2){
				vec2.push_back(item);
			}
			std::sort(vec1.begin(), vec1.end());
			std::sort(vec2.begin(), vec2.end());
			return vec1 == vec2;
		}
		void testCase1(){
			stdUst<int> ust1(10);
			tsUst<int> ust2(10);
			assert(container_equal(ust1, ust2));

			int arr[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			stdUst<int> ust3(std::begin(arr), std::end(arr));
			tsUst<int> ust4(std::begin(arr), std::end(arr));
			assert(container_equal(ust3, ust4));

			auto ust5(ust3);
			auto ust6(ust4);
			assert(container_equal(ust5, ust6));

			auto ust7 = ust3;
			auto ust8 = ust4;
			assert(container_equal(ust7, ust8));
		}
		void testCase2(){
			tsUst<int> ust1(10);
			assert(ust1.empty());
			assert(ust1.size() == 0);

			int arr[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			tsUst<int> ust2(std::begin(arr), std::end(arr));
			assert(!ust2.empty());
			assert(ust2.size() == 10);
		}
		void testCase3(){
			tsUst<std::string> ust1(10);
			stdUst<std::string> ust2(10);
			std::random_device rd;
			for (auto i = 0; i != 100; ++i){
				auto n = std::to_string(rd() % 65536);
				ust1.insert(n);
				ust2.insert(n);
			}
			assert(container_equal(ust1, ust2));

			tsUst<int> ust3(10);
			stdUst<int> ust4(10);
			std::vector<int> v(200);
			std::generate(v.begin(), v.end(), [&rd](){return rd() % 65536; });
			ust3.insert(v.begin(), v.end());
			ust4.insert(v.begin(), v.end());
			assert(container_equal(ust3, ust4));
		}
		void testCase4(){
			int arr[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			stdUst<int> ust1(std::begin(arr), std::end(arr));
			tsUst<int> ust2(std::begin(arr), std::end(arr));

			ust1.erase(9);
			auto n = ust2.erase(9);
			assert(n == 1);
			ust1.erase(7);
			auto it = ust2.find(7);
			it = ust2.erase(it);
			assert(it != ust2.end());
			assert(container_equal(ust1, ust2));
		}
		void testCase5(){
			int arr[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 7, 8, 9 };
			tsUst<int> ust(std::begin(arr), std::end(arr));

			assert(ust.find(0) != ust.end());
			assert(ust.count(10) == 0);
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