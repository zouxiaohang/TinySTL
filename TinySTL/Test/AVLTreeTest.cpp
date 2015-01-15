#include "AVLTreeTest.h"

namespace TinySTL{
	namespace AVLTreeTest{
		template<class Container1, class Container2>
		bool container_equal(const Container1& con1, const Container2& con2){
			auto first1 = con1.cbegin(), last1 = con1.cend();
			auto first2 = con2.cbegin(), last2 = con2.cend();
			for (; first1 != last1 && first2 != last2; ++first1, ++first2){
				if (*first1 != *first2)
					return false;
			}
			return (first1 == last1 && first2 == last2);
		}


		void testCase1(){
			tsAVL<std::string> avl;
			assert(avl.empty());
			assert(avl.size() == 0);

			avl.insert("0");
			assert(!avl.empty());
			assert(avl.size() == 1);
			assert(*avl.root() == "0");
		}
		void testCase2(){
			tsAVL<int> avl;
			for (auto i = 0; i != 10000; ++i){
				avl.insert(i);
			}
			assert(avl.height() == 14);
		}
		void testCase3(){
			tsAVL<int> avl;
			for (auto i = 0; i != 10; ++i){
				avl.insert(i);
			}
			assert(*avl.find(5) == 5);
			assert(*avl.find_min() == 0);
			assert(*avl.find_max() == 9);
		}
		void testCase4(){
			tsAVL<int> avl;
			std::vector<int> v;
			std::random_device rd;

			for (auto i = 0; i != 100; ++i){
				auto r = rd() % 65536;
				avl.insert(r);
				v.push_back(r);
			}
			std::sort(v.begin(), v.end());
			v.erase(std::unique(v.begin(), v.end()), v.end());
			assert(container_equal(avl, v));

			for (auto i = 0; i != 20; ++i){
				avl.erase(*avl.cbegin());
				v.erase(v.begin());
				assert(container_equal(avl, v));
			}

			tsAVL<int> avl1;
			avl1.insert(v.begin(), v.end());
			assert(container_equal(avl1, v));
		}

		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
			testCase4();
		}
	}
}