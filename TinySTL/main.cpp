#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <utility>

#include <boost\circular_buffer.hpp>

#include "CircularBuffer.h"
#include "Profiler\Profiler.h"

using namespace std;
using namespace TinySTL::Profiler;

int main(){
	TinySTL::circular_buffer<int, 10000> cb(10000, 0);
	//boost::circular_buffer<int> cb(10000, 0);
	ProfilerInstance::start();
	for (int i = 0; i != 100; ++i){
		cb.push_back(i);
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
	system("pause");
	return 0;
}
