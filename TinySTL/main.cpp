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

#include "Queue.h"

using namespace TinySTL::Profiler;
class mycomparison
{
	bool reverse;
public:
	mycomparison(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (const int& lhs, const int&rhs) const
	{
		if (reverse) return (lhs>rhs);
		else return (lhs<rhs);
	}
};
int main(){
	int array[] = { 1, 2, 3, 4, 5 };
	TinySTL::vector<int> myvector(array, array+5);

	std::cout << "myvector backwards:";
	for (auto rit = myvector.crbegin(); rit != myvector.crend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';
	system("pause");
	return 0;
}
