#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <mutex>
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <thread>
#include <utility>

#include <boost\circular_buffer.hpp>

#include "Algorithm.h"
#include "String.h"
#include "Vector.h"
#include "Profiler\Profiler.h"

using namespace TinySTL::Profiler;

int main(){
	/*char array[] = "+C";
	TinySTL::string s("LoveC++");
	TinySTL::string str("ZXHLoveC++VeryMuch");
	cout << str.find_first_of(array, 0, str.size()) << endl;*/
	TinySTL::string name("zxh");
	//std::string name("zxh");

	std::cout << "Please, enter your full name: ";
	TinySTL::getline(std::cin, name,'i');
	//std::getline(std::cin, name);
	std::cout << name << "\n";
	system("pause");
	return 0;
}
