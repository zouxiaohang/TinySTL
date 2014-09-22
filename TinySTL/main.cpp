#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "Allocator.h"
#include "Construct.h"
#include "Vector.h"
#include "Profiler\Profiler.h"
#include "UninitializedFunctions.h"

using namespace std;
using namespace TinySTL::Profiler;

int main(){
	
	int array[100000] = { 1 };
	std::vector<int> vec;
	//TinySTL::vector<int> vec;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 10000000; ++i){
		//vec.insert(vec.end(), array, array + 1);
		vec.push_back(i);
	}
	//vec.insert(vec.end(), array, array + 100000);
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
	system("pause");
	return 0;
}
