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
	
	//std::vector<std::string> vec;
	//TinySTL::vector<std::string> vec;
	TinySTL::vector<int> vec;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 10000; ++i){
		//vec.push_back(std::string("zouxiaohang"));
		vec.push_back(i);
	}
	//for (auto i : vec){ cout << i << endl; }
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
	system("pause");
	return 0;
}
