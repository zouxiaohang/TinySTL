#include <iostream>
#include <array>

#include "..\Algorithm.h"
#include "..\Vector.h"

using namespace TinySTL;

int main(){
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
	system("pause");
	return 0;
}