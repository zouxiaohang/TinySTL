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
	TinySTL::vector<std::string> svec(10, "hello world");
	for (auto s : svec){ cout << s << endl; }
	system("pause");
	return 0;
}
