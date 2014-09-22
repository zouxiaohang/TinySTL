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
	
	std::vector<std::string> vec;
	//TinySTL::vector<std::string> vec;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 100000; ++i){
		vec.push_back(std::string("zouxiaohang"));
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
	system("pause");
	return 0;
}
