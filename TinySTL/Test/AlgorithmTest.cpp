#include <iostream>
#include <array>
#include <cstring>
#include <cctype>

#include "..\Algorithm.h"
#include "..\Vector.h"

using namespace TinySTL;

void myfunction(int i) {  // function:
	std::cout << ' ' << i;
}
struct myclass {           // function object type:
	void operator() (int i) { std::cout << ' ' << i; }
} myobject;
bool IsOdd(int i) {
	return ((i % 2) == 1);
}
bool myfunction2(int i, int j) {
	return (i == j);
}
bool comp_case_insensitive(char c1, char c2) {
	return (std::tolower(c1) == std::tolower(c2));
}
void testAlgorithm(){
	//test fill
	vector<int> myvector1(8);                       // myvector: 0 0 0 0 0 0 0 0
	fill(myvector1.begin(), myvector1.begin() + 4, 5);   // myvector: 5 5 5 5 0 0 0 0
	fill(myvector1.begin() + 3, myvector1.end() - 2, 8);   // myvector: 5 5 5 8 8 8 0 0
	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector1.begin(); it != myvector1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//test fill_n
	vector<int> myvector2(8, 10);        // myvector: 10 10 10 10 10 10 10 10
	fill_n(myvector2.begin(), 4, 20);     // myvector: 20 20 20 20 10 10 10 10
	fill_n(myvector2.begin() + 3, 3, 33);   // myvector: 20 20 20 33 33 33 10 10
	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector2.begin(); it != myvector2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//test min
	std::cout << "min(1,2)==" << min(1, 2) << '\n';
	std::cout << "min(2,1)==" << min(2, 1) << '\n';
	std::cout << "min('a','z')==" << min('a', 'z') << '\n';
	std::cout << "min(3.14,2.72)==" << min(3.14, 2.72) << '\n';

	//test max
	std::cout << "max(1,2)==" << max(1, 2) << '\n';
	std::cout << "max(2,1)==" << max(2, 1) << '\n';
	std::cout << "max('a','z')==" << max('a', 'z') << '\n';
	std::cout << "max(3.14,2.73)==" << max(3.14, 2.73) << '\n';

	//test make_heap¡¢pop_heap¡¢push_heap¡¢sort_heap
	int myints[] = { 10, 20, 30, 5, 15 };
	vector<int> v(myints, myints + 5);
	make_heap(v.begin(), v.end());
	std::cout << "initial max heap   : " << v.front() << '\n';
	pop_heap(v.begin(), v.end()); v.pop_back();
	std::cout << "max heap after pop : " << v.front() << '\n';
	v.push_back(99); 
	push_heap(v.begin(), v.end());
	std::cout << "max heap after push: " << v.front() << '\n';
	sort_heap(v.begin(), v.end());
	std::cout << "final sorted range :";
	for (unsigned i = 0; i<v.size(); i++)
		std::cout << ' ' << v[i];
	std::cout << '\n';

	//test is_heap
	vector<int> foo;
	foo.push_back(9), foo.push_back(5), foo.push_back(2), foo.push_back(6);
	foo.push_back(4), foo.push_back(1), foo.push_back(3), foo.push_back(8);
	foo.push_back(7);
	if (!std::is_heap(foo.begin(), foo.end()))
		std::make_heap(foo.begin(), foo.end());
	std::cout << "Popping out elements:";
	while (!foo.empty()) {
		std::pop_heap(foo.begin(), foo.end());   // moves largest element to back
		std::cout << ' ' << foo.back();         // prints back
		foo.pop_back();                         // pops element out of container
	}
	std::cout << '\n';

	//test all_of
	std::array<int, 8> foo1 = { 3, 5, 7, 11, 13, 17, 19, 23 };
	if (TinySTL::all_of(foo1.begin(), foo1.end(), [](int i){return i % 2; }))
		std::cout << "All the elements are odd numbers.\n";

	//test any_of
	std::array<int, 7> foo2 = { 0, 1, -1, 3, -3, 5, -5 };
	if (TinySTL::any_of(foo2.begin(), foo2.end(), [](int i){return i<0; }))
		std::cout << "There are negative elements in the range.\n";

	//test none_of
	std::array<int, 8> foo3 = { 1, 2, 4, 8, 16, 32, 64, 128 };
	if (TinySTL::none_of(foo3.begin(), foo3.end(), [](int i){return i<0; }))
		std::cout << "There are no negative elements in the range.\n";

	//test for_each
	vector<int> myvector3;
	myvector3.push_back(10);
	myvector3.push_back(20);
	myvector3.push_back(30);
	std::cout << "myvector contains:";
	for_each(myvector3.begin(), myvector3.end(), myfunction);
	std::cout << '\n';
	std::cout << "myvector contains:";
	for_each(myvector3.begin(), myvector3.end(), myobject);
	std::cout << '\n';

	//test find
	int myints1[] = { 10, 20, 30, 40 };
	int * p;
	p = std::find(myints1, myints1 + 4, 30);
	if (p != myints1 + 4)
		std::cout << "Element found in myints: " << *p << '\n';
	else
		std::cout << "Element not found in myints\n";
	vector<int> myvector4(myints1, myints1 + 4);
	vector<int>::iterator it;
	it = find(myvector4.begin(), myvector4.end(), 30);
	if (it != myvector4.end())
		std::cout << "Element found in myvector: " << *it << '\n';
	else
		std::cout << "Element not found in myints\n";

	//test find_if
	vector<int> myvector5;
	myvector5.push_back(10);
	myvector5.push_back(25);
	myvector5.push_back(40);
	myvector5.push_back(55);
	vector<int>::iterator it4 = find_if(myvector5.begin(), myvector5.end(), IsOdd);
	std::cout << "The first odd value is " << *it4 << '\n';

	//test find_if_not
	std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
	auto it5 = TinySTL::find_if_not(arr.begin(), arr.end(), [](int i){return i % 2; });
	std::cout << "The first even value is " << *it5 << '\n';

	//test find_end
	int myints2[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
	vector<int> haystack(myints2, myints2 + 10);
	int needle1[] = { 1, 2, 3 };
	vector<int>::iterator it6;
	it6 = find_end(haystack.begin(), haystack.end(), needle1, needle1 + 3);
	if (it6 != haystack.end())
		std::cout << "needle1 last found at position " << (it6 - haystack.begin()) << '\n';
	int needle2[] = { 4, 5, 1 };
	it6 = find_end(haystack.begin(), haystack.end(), needle2, needle2 + 3, myfunction2);
	if (it6 != haystack.end())
		std::cout << "needle2 last found at position " << (it6 - haystack.begin()) << '\n';

	//test find_first_of
	int mychars[] = { 'a', 'b', 'c', 'A', 'B', 'C' };
	vector<char> haystack1(mychars, mychars + 6);
	vector<char>::iterator it7;
	int needle[] = { 'A', 'B', 'C' };
	it7 = find_first_of(haystack1.begin(), haystack1.end(),
		needle, needle + 3, comp_case_insensitive);
	if (it7 != haystack1.end())
		std::cout << "The first match is: " << *it7 << '\n';

	//test adjacent_find
	int myints3[] = { 5, 20, 5, 30, 30, 20, 10, 10, 20 };
	vector<int> v1(myints3, myints3 + 8);
	vector<int>::iterator it8;
	it8 = adjacent_find(v1.begin(), v1.end());
	if (it8 != v1.end())
		std::cout << "the first pair of repeated elements are: " << *it8 << '\n';
	it8 = adjacent_find(++it8, v1.end(), myfunction2);
	if (it8 != v1.end())
		std::cout << "the second pair of repeated elements are: " << *it8 << '\n';

	//test count
	int myints4[] = { 10, 20, 30, 30, 20, 10, 10, 20 };   // 8 elements
	int mycount = std::count(myints4, myints4 + 8, 10);
	std::cout << "10 appears " << mycount << " times.\n";
	vector<int> myvector6(myints4, myints4 + 8);
	mycount = count(myvector6.begin(), myvector6.end(), 20);
	std::cout << "20 appears " << mycount << " times.\n";

	//test mismatch
	vector<int> myvector7;
	for (int i = 1; i<6; i++) myvector7.push_back(i * 10); // myvector: 10 20 30 40 50
	int myints5[] = { 10, 20, 80, 320, 1024 };                //   myints: 10 20 80 320 1024
	pair<vector<int>::iterator, int*> mypair;
	mypair = mismatch(myvector7.begin(), myvector7.end(), myints5);
	std::cout << "First mismatching elements: " << *mypair.first;
	std::cout << " and " << *mypair.second << '\n';
	++mypair.first; ++mypair.second;
	mypair = mismatch(mypair.first, myvector7.end(), mypair.second, myfunction2);
	std::cout << "Second mismatching elements: " << *mypair.first;
	std::cout << " and " << *mypair.second << '\n';

}