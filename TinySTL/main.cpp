#include <iostream>
#include <memory>

#include "Alloc.h"
#include "Construct.h"

using namespace std;

int main(){
	for (int i = 1; i != 100000; ++i){
		TinySTL::alloc::allocate(i % 128 * sizeof(int));
		//std::allocator<int> alloc; alloc.allocate(i % 128);
		//malloc(i % 128 * sizeof(int));
	}
	system("pause");
	return 0;
}