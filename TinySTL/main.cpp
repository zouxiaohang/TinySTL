#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "Vector.h"
#include "Profiler\Profiler.h"

using namespace std;
using namespace TinySTL::Profiler;

int main(){
	
	//std::vector<std::string> vec;
	////TinySTL::vector<std::string> vec;
	//ProfilerInstance::start();
	//int i = 0;
	//for (; i != 1000; ++i){
	//	vec.push_back(std::string("zouxiaohang"));
	//}
	//ProfilerInstance::finish();
	//ProfilerInstance::dumpDuringTime();
	TinySTL::vector<int> v(10, 1);
	for (auto i : v){ cout << i << endl; }
	cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;
	v.resize(9);
	for (auto i : v){ cout << i << endl; }
	cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;
	v.resize(20, -1);
	for (auto i : v){ cout << i << endl; }
	cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;
	v.push_back(0);
	cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;
	system("pause");
	return 0;
}
