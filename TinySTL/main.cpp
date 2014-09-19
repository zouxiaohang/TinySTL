#include <iostream>
#include <memory>

#include "Allocator.h"
#include "Construct.h"
#include "UninitializedFunctions.h"

using namespace std;

int main(){
	/*for (int i = 1; i != 100000; ++i){
		auto p = TinySTL::allocator<int>::allocate();
		
	}*/
	auto p = TinySTL::allocator<int>::allocate(100);
	TinySTL::uninitialized_fill(p, p + 100, 88);
	auto last = p + 100;
	int array[100];
	TinySTL::uninitialized_fill_n(array, 100, 88);
	for (auto n : array){ cout << n << endl; }
	system("pause");
	return 0;
}