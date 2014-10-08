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

#include "Bitmap.h"
#include "Profiler\Profiler.h"

using namespace std;
using namespace TinySTL::Profiler;

int main(){
	std::string str("abcdefghijklmnpqrstuvwxyz");
	TinySTL::bitmap<26> bm;
	for (auto it = str.cbegin(); it != str.cend(); ++it){
		bm.set(*it - 'a');
	}
	cout << bm << endl;
	cout << bm.size() << endl;
	system("pause");
	return 0;
}
