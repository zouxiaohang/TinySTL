#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "Allocator.h"
#include "Construct.h"
#include "Vector.h"
#include "UninitializedFunctions.h"

using namespace std;

int main(){
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//TinySTL::vector<int> svec(array, array + 5);
	//svec.erase(svec.begin() + 1, svec.begin() + 4);//1,5
	TinySTL::vector<int> svec(10, 0);
	svec.insert(svec.begin() + 0, array, array + 10);
	//svec.insert(svec.begin()+0, 10, 99);
	for (auto s : svec){ cout << s << endl; }
	system("pause");
	return 0;
}
