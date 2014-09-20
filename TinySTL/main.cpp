#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Allocator.h"
#include "Construct.h"
#include "Vector.h"
#include "UninitializedFunctions.h"

using namespace std;

int main(){
	int array[3] = { 1, 2, 3 };
	TinySTL::vector<int> vec(array, array + 3);
	//TinySTL::vector<int> vec(3, 1); -> error C2019
	cout << *(vec.begin()) << endl;
	cout << *(++vec.begin()) << endl;
	cout << *(--vec.end()) << endl;
	system("pause");
	return 0;
}