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
	}
}

using namespace TinySTL::AlgorithmTest;
int main(){
	//testFill();
	//testFillN();
	//testMinMax();
	//testHeapAlgorithm();
	//testIsHeap();
	//testAllOf();
	//testNoneOf();
	//testAnyOf();
	//testForEach();
	system("pause");
	return 0;
}