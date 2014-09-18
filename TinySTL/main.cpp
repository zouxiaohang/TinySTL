#include <iostream>
#include <memory>

#include "Allocator.h"
#include "Construct.h"

using namespace std;

int main(){
	for (int i = 1; i != 100000; ++i){
		auto p = TinySTL::allocator<int>::allocate();
		TinySTL::allocator<int>::construct(p, i);
		TinySTL::allocator<int>::destroy(p);
		TinySTL::allocator<int>::deallocate(p);
	}
	system("pause");
	return 0;
}