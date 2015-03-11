#include "AlgorithmTest.h"

namespace TinySTL{
	namespace AlgorithmTest{
		void testFill(){
			std::vector<int> v1(8), v2(8);
			std::fill(v1.begin(), v1.begin() + 4, 5);   //5 5 5 5 0 0 0 0
			std::fill(v1.begin() + 3, v1.end() - 2, 8);   //5 5 5 8 8 8 0 0
			TinySTL::fill(v2.begin(), v2.begin() + 4, 5);   //5 5 5 5 0 0 0 0
			TinySTL::fill(v2.begin() + 3, v2.end() - 2, 8);   //5 5 5 8 8 8 0 0

			assert(TinySTL::Test::container_equal(v1, v2));
		}
		void testFillN(){
			std::vector<int> v1(8, 10), v2(8, 10);
			std::fill_n(v1.begin(), 4, 20);     //20 20 20 20 10 10 10 10
			std::fill_n(v1.begin() + 3, 3, 33);   //20 20 20 33 33 33 10 10
			TinySTL::fill_n(v2.begin(), 4, 20);     //20 20 20 20 10 10 10 10
			TinySTL::fill_n(v2.begin() + 3, 3, 33);   //20 20 20 33 33 33 10 10

			assert(TinySTL::Test::container_equal(v1, v2));
		}
		void testMinMax(){
			assert(TinySTL::min(1, 2) == 1);
			assert(TinySTL::min(2, 1) == 1);
			assert(TinySTL::min('a', 'z') == 'a');
			assert(TinySTL::min(3.14, 2.72) == 2.72);

			assert(TinySTL::max(1, 2) == 2);
			assert(TinySTL::max(2, 1) == 2);
			assert(TinySTL::max('a', 'z') == 'z');
			assert(TinySTL::max(3.14, 2.73) == 3.14);
		}
		void testHeapAlgorithm(){
			int myints[] = { 10, 20, 30, 5, 15 };
			std::vector<int> v1(myints, myints + 5);
			std::vector<int> v2(myints, myints + 5);

			std::make_heap(v1.begin(), v1.end());
			TinySTL::make_heap(v2.begin(), v2.end());
			assert(TinySTL::Test::container_equal(v1, v2));

			std::pop_heap(v1.begin(), v1.end()); v1.pop_back();
			TinySTL::pop_heap(v2.begin(), v2.end()); v2.pop_back();
			assert(TinySTL::Test::container_equal(v1, v2));

			v1.push_back(99); std::push_heap(v1.begin(), v1.end());
			v2.push_back(99); TinySTL::push_heap(v2.begin(), v2.end());
			assert(TinySTL::Test::container_equal(v1, v2));

			std::sort_heap(v1.begin(), v1.end());
			TinySTL::sort_heap(v2.begin(), v2.end());
			assert(TinySTL::Test::container_equal(v1, v2));
		}
		void testIsHeap(){
			std::vector<int> v1{ 9, 5, 2, 6, 4, 1, 3, 8, 7 };
			std::vector<int> v2{ 9, 5, 2, 6, 4, 1, 3, 8, 7 };

			if (!std::is_heap(v1.begin(), v1.end()))
				std::make_heap(v1.begin(), v1.end());
			if (!TinySTL::is_heap(v2.begin(), v2.end()))
				TinySTL::make_heap(v2.begin(), v2.end());

			assert(TinySTL::Test::container_equal(v1, v2));
		}
		void testAllOf(){
			std::array<int, 8> foo = { 3, 5, 7, 11, 13, 17, 19, 23 };
			assert(TinySTL::all_of(foo.begin(), foo.end(), [](int i){return i % 2; }));
		}
		void testNoneOf(){
			std::array<int, 8> foo = { 1, 2, 4, 8, 16, 32, 64, 128 };
			assert(TinySTL::none_of(foo.begin(), foo.end(), [](int i){return i < 0; }));
		}
		void testAnyOf(){
			std::array<int, 7> foo = { 0, 1, -1, 3, -3, 5, -5 };
			assert(std::any_of(foo.begin(), foo.end(), [](int i){return i < 0; }));
		}
		void testForEach(){
			std::vector<int> myvector{ 10, 20, 30 };
			std::vector<int> temp{ 11, 21, 31 };
			TinySTL::for_each(myvector.begin(), myvector.end(), [&myvector](int& i){
					++i;
			});

			assert(TinySTL::Test::container_equal(myvector, temp));
		}
		void testFind(){
			std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			assert(TinySTL::find(v.begin(), v.end(), 5) != v.end());
			assert(TinySTL::find(v.begin(), v.end(), 10) == v.end());

			assert(TinySTL::find_if(v.begin(), v.end(), [](int i){return i < 0; }) == v.end());
			assert(TinySTL::find_if_not(v.begin(), v.end(), [](int i){return i < 0; }) != v.end());
		}
		void testFindEnd(){
			int myints[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
			std::vector<int> v(myints, myints + 10);
			int needle1[] = { 1, 2, 3 };
			auto it = TinySTL::find_end(v.begin(), v.end(), needle1, needle1 + 3);
			assert(it == v.begin() + 5);

			int needle2[] = { 4, 5, 1 };
			it = TinySTL::find_end(v.begin(), v.end(), needle2, needle2 + 3, [](int i, int j){return i == j; });
			assert(it == v.begin() + 3);
		}
		void testFindFirstOf(){
			int mychars[] = { 'a', 'b', 'c', 'A', 'B', 'C' };
			std::vector<char> v(mychars, mychars + 6);
			int needle[] = { 'A', 'B', 'C' };
			auto it = TinySTL::find_first_of(v.begin(), v.end(), needle, needle + 3);
			assert(*it == 'A');

			it = TinySTL::find_first_of(v.begin(), v.end(), needle, needle + 3,
				[](char ch1, char ch2){return std::tolower(ch1) == std::tolower(ch2); });
			assert(*it == 'a');
		}
		void testAdjacentFind(){
			int myints[] = { 5, 20, 5, 30, 30, 20, 10, 10, 20 };
			std::vector<int> v(myints, myints + 8);
			auto it = TinySTL::adjacent_find(v.begin(), v.end());
			assert(*it == 30);

			it = TinySTL::adjacent_find(++it, v.end(), [](int i, int j){return i == j; });
			assert(*it == 10);
		}
		void testCount(){
			int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };   // 8 elements
			int mycount = TinySTL::count(myints, myints + 8, 10);
			assert(mycount == 3);

			mycount = TinySTL::count_if(myints, myints + 8, [](int i){return i % 2 == 0; });
			assert(mycount == 8);
		}
		void testMismatch(){
			std::vector<int> v;
			for (int i = 1; i<6; i++) v.push_back(i * 10); //10 20 30 40 50
			int myints[] = { 10, 20, 80, 320, 1024 };
			TinySTL::pair<std::vector<int>::iterator, int*> mypair;
			mypair = TinySTL::mismatch(v.begin(), v.end(), myints);
			assert(*mypair.first == 30 && *mypair.second == 80);

			++mypair.first; ++mypair.second;
			mypair = TinySTL::mismatch(mypair.first, v.end(), mypair.second, [](int i, int j){return i == j; });
		}
		void testEqual(){
			int myints[] = { 20, 40, 60, 80, 100 };
			std::vector<int>v(myints, myints + 5);     //20 40 60 80 100
			assert(TinySTL::equal(v.begin(), v.end(), myints));

			v[3] = 81;
			assert(!TinySTL::equal(v.begin(), v.end(), myints, [](int i, int j){return i == j; }));
		}
		void testIsPermutation(){
			std::array<int, 5> foo = { 1, 2, 3, 4, 5 };
			std::array<int, 5> bar = { 3, 1, 4, 5, 2 };

			assert(TinySTL::is_permutation(foo.begin(), foo.end(), bar.begin()));
		}
		void testSearch(){
			std::vector<int> v;
			for (int i = 1; i<10; i++) v.push_back(i * 10);
			int needle1[] = { 40, 50, 60, 70 };
			auto it = TinySTL::search(v.begin(), v.end(), needle1, needle1 + 4);
			assert(it == v.begin() + 3);

			int needle2[] = { 20, 30, 50 };
			it = std::search(v.begin(), v.end(), needle2, needle2 + 3, [](int i, int j){return i == j; });
			assert(it == v.end());
		}
		void testAdvance(){
			TinySTL::vector<int> v;
			TinySTL::list<int> l;
			TinySTL::binary_search_tree<int> bst;
			for (auto i = 0; i != 10; ++i){
				v.push_back(i);
				l.push_back(i);
				bst.insert(i);
			}
			auto vit = v.begin();
			auto lit = l.begin();
			auto bit = bst.cbegin();

			TinySTL::advance(vit, 5);
			TinySTL::advance(lit, 5);
			TinySTL::advance(bit, 5);
			assert(*vit == 5 && *lit == 5 && *bit == 5);

			TinySTL::advance(vit, -5);
			TinySTL::advance(lit, -5);
			assert(*vit == 0 && *lit == 0);
		}
		void testSort(){
			int arr1[1] = { 0 };
			TinySTL::sort(std::begin(arr1), std::end(arr1));
			assert(std::is_sorted(std::begin(arr1), std::end(arr1)));

			int arr2[2] = { 1, 0 };
			TinySTL::sort(std::begin(arr2), std::end(arr2));
			assert(std::is_sorted(std::begin(arr2), std::end(arr2)));

			int arr3[3] = { 2, 1, 3 };
			TinySTL::sort(std::begin(arr3), std::end(arr3));
			assert(std::is_sorted(std::begin(arr3), std::end(arr3)));

			int arr4[100];
			std::random_device rd;
			for (auto i = 0; i != 10; ++i){
				for (auto& n : arr4){
					n = rd() % 65536;
				}
				TinySTL::sort(std::begin(arr4), std::end(arr4));
				assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
			}
		}
		void testGenerate(){
			int arr1[100], arr2[100];
			auto f = [](int i){ return i; };
			for (auto i = 0; i != 100; ++i){
				auto func = std::bind(f, i);
				TinySTL::generate(std::begin(arr1), std::end(arr1), func);
				std::generate(std::begin(arr2), std::end(arr2), func);
			}
			assert(TinySTL::Test::container_equal(arr1, arr2));

			int n1 = 0, n2 = 0;
			auto gen1 = [&n1](){return n1++; };
			auto gen2 = [&n2](){return n2++; };
			int arr3[100], arr4[100];
			TinySTL::generate_n(arr3, 100, gen1);
			std::generate_n(arr4, 100, gen2);
			assert(TinySTL::Test::container_equal(arr3, arr4));
		}
		void testDistance(){
			TinySTL::list<int> l(10, 0);
			TinySTL::vector<int> v(10, 0);

			auto lit = l.begin();
			TinySTL::advance(lit, 5);
			auto vit = v.begin();
			TinySTL::advance(vit, 5);

			assert(TinySTL::distance(l.begin(), lit) == 5);
			assert(TinySTL::distance(v.begin(), vit) == 5);
		}
		void testCopy(){
			char arr1[] = "hello", res1[6] = { 0 };
			TinySTL::copy(std::begin(arr1), std::end(arr1), res1);
			assert(TinySTL::Test::container_equal(arr1, res1));

			wchar_t arr2[] = L"hello", res2[6] = { 0 };
			TinySTL::copy(std::begin(arr2), std::end(arr2), res2);
			assert(TinySTL::Test::container_equal(arr2, res2));

			int arr3[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, res3[10] = { 0 };
			TinySTL::copy(std::begin(arr3), std::end(arr3), res3);
			assert(TinySTL::Test::container_equal(arr3, res3));

			std::string arr4[3] = { "1", "2", "3" }, res4[3];
			TinySTL::copy(std::begin(arr4), std::end(arr4), res4);
			assert(TinySTL::Test::container_equal(arr4, res4));
		}

		void testAllCases(){
			testFill();
			testFillN();
			testMinMax();
			testHeapAlgorithm();
			testIsHeap();
			testAllOf();
			testNoneOf();
			testAnyOf();
			testForEach();
			testFind();
			testFindEnd();
			testFindFirstOf();
			testAdjacentFind();
			testCount();
			testMismatch();
			testEqual();
			testIsPermutation();
			testSearch();
			testAdvance();
			testSort();
			testGenerate();
			testDistance();
			testCopy();
		}
	}
}