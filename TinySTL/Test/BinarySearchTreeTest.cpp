#include "BinarySearchTreeTest.h"

namespace TinySTL{
	namespace BinarySearchTreeTest{
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
			tsBst<std::string> bst;

			assert(bst.empty());
			assert(bst.size() == 0);

			bst.insert("1");
			assert(!bst.empty());
			assert(bst.size() == 1);
		}
		void testCase2(){
			tsBst<int> bst;

			for (auto i = 0; i != 100; ++i)
				bst.insert(i);
			assert(bst.height() == 100);
		}
		void testCase3(){
			tsBst<int> bst;
			std::vector<int> v;
			std::random_device rd;

			for (auto i = 0; i != 100; ++i){
				auto r = rd() % 65536;
				bst.insert(r);
				v.push_back(r);
			}
			std::sort(v.begin(), v.end());
			v.erase(std::unique(v.begin(), v.end()), v.end());
			assert(container_equal(bst, v));

			for (auto i = 0; i != 20; ++i){
				bst.erase(*bst.cbegin());
				v.erase(v.begin());
				assert(container_equal(bst, v));
			}
			
			tsBst<int> bst1;
			bst1.insert(v.begin(), v.end());
			assert(container_equal(bst1, v));
		}
		void testCase4(){
			tsBst<int> bst;
			for (auto i = 0; i != 10; ++i)
				bst.insert(i);

			assert(*bst.find(5) == 5);
			assert(*bst.find_min() == 0);
			assert(*bst.find_max() == 9);
		}


		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
			testCase4();
		}
	}
}